#ifndef THORSANVIL_STREAM_THOR_STREAM_H
#define THORSANVIL_STREAM_THOR_STREAM_H

#include "ThorsSimpleStream.h"
#include <thread>
#include <iostream>

namespace ThorsAnvil
{
    namespace Stream
    {

class IThorStream: public std::istream
{
    // Class to handle the down-loading of all http connections in the background.
    class ThorStreamManager
    {
        public:
            // Everybody will use the same instance
            static ThorStreamManager& defaultManager()
            {
                static ThorStreamManager defaultManager;
                return defaultManager;
            }

            ThorStreamManager()
                : finished(false)
                , multi(curl_multi_init())
                , streamThread(&ThorStreamManager::eventLoop, this, multi != NULL)
            {
                if (multi == NULL)
                {   throw std::runtime_error("Failed to startup");
                }
            }
            ~ThorStreamManager()
            {
                // When destroying the object.
                // Make sure we first take care of any threads.
                {
                    std::unique_lock<std::mutex> lock(mutex);
                    finished    = true;
                }
                cond.notify_one();
                streamThread.join();

                // Now we can clean up any resources.
                curl_multi_cleanup(multi);
            }

            // Interface to add/remove http requests.
            void addHTTPRequest(CURL* easy)
            {
                std::unique_lock<std::mutex> lock(mutex);
                curl_multi_add_handle(multi, easy);
            }
            void delHTTPRequest(CURL* easy)
            {
                std::unique_lock<std::mutex> lock(mutex);
                curl_multi_remove_handle(multi, easy);
            }

        private:
            // Event loop is run by the thread.
            // It handles all interactions with sockets.
            void eventLoop(bool ok);

            bool                        finished;
            CURLM*                      multi;
            std::mutex                  mutex;
            std::condition_variable     cond;
            std::thread                 streamThread;
    };
    // The stream buffer.
    class SocketStreamBuffer: public IThorSimpleStream::SimpleSocketStreamBuffer
    {
        public:
        typedef IThorSimpleStream::SimpleSocketStreamBuffer::traits_type    traits;
        typedef traits::int_type                                            int_type;

        SocketStreamBuffer(std::string const& url, std::function<void()> markStreamBad)
            : SimpleSocketStreamBuffer(url, IThorSimpleStream::Manually, IThorSimpleStream::OneBlock, markStreamBad)
        {
            /* Perform the request, res will get the return code */
            ThorStreamManager::defaultManager().addHTTPRequest(curl);
        }
        ~SocketStreamBuffer()
        {
            ThorStreamManager::defaultManager().delHTTPRequest(curl);
        }
        virtual int_type underflow()
        {
            {
                std::unique_lock<std::mutex> lock(mutex);
                empty = true;
            }
            curl_easy_pause(curl, CURLPAUSE_CONT);
            {
                bool& open  = this->open;
                bool& empty = this->empty;
                std::unique_lock<std::mutex> lock(mutex);
                cond.wait(lock, [&empty, &open](){return !(empty && open);});
            }
            return empty ? EOF : buffer[0];
        }
        // Used by ThorStreamManager to mark that the stream has
        // finished downloading data.
        virtual void markAsDone()
        {
            std::unique_lock<std::mutex> lock(mutex);
            open    = false;
            cond.notify_one();
        }

    };

    SocketStreamBuffer    buffer;

    public:
        IThorStream(std::string const& url)
            : std::istream(NULL)
            , buffer(url, [this](){this->setstate(std::ios::badbit);})
        {
            std::istream::rdbuf(&buffer);
        }
};

    }
}

#if defined(HEADER_ONLY) && HEADER_ONLY == 1
#include "ThorsStream.source"
#endif


#endif
