
#ifndef THORSANVIL_SIMPLE_STREAM_THOR_STREAM_H
#define THORSANVIL_SIMPLE_STREAM_THOR_STREAM_H

#include <istream>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <curl/curl.h>
#include <string.h>
#include <cstdlib>

namespace ThorsAnvil
{
    namespace Stream
    {

extern "C"  size_t writeFunc(char* ptr, size_t size, size_t nmemb, void* userdata);
extern "C"  size_t headFunc(char* ptr, size_t size, size_t nmemb, void* userdata);

class IThorStream;
class IThorSimpleStream: public std::istream
{
    friend class IThorStream;
    struct SimpleSocketStreamBuffer: public std::streambuf
    {
        typedef std::streambuf::traits_type traits;
        typedef traits::int_type            int_type;
 
        SimpleSocketStreamBuffer(std::string const& url, bool useEasyCurl, bool preDownload, std::function<void()> markStreamBad)
            : empty(true)
            , open(true)
            , sizeMarked(false)
            , droppedData(false)
            , preDownload(preDownload)
            , sizeLeft(0)
            , markStreamBad(markStreamBad)
        {
            curl = curl_easy_init();
            if(!curl)
            {   markStreamBad();
            }
            curl_easy_setopt(curl, CURLOPT_URL,                 url.c_str());
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION,      1L);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,       writeFunc);
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION,      headFunc);
            curl_easy_setopt(curl, CURLOPT_WRITEHEADER,         this);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA,           this);
            curl_easy_setopt(curl, CURLOPT_PRIVATE,             this);

            if (useEasyCurl)
            {
                /* Perform the request, res will get the return code */
                CURLcode result = curl_easy_perform(curl);
                if ((result != CURLE_OK) && (result != CURLE_WRITE_ERROR))
                {   markStreamBad();
                }
            }
        }
        ~SimpleSocketStreamBuffer()
        {
            curl_easy_cleanup(curl);
        }
        virtual int_type underflow()
        {
            if (droppedData)
            {   markStreamBad();
            }

            return EOF;
        }
        protected:
            friend size_t writeFunc(char* ptr, size_t size, size_t nmemb, void* userdata)
            {
                std::size_t     bytes = size*nmemb;

                SimpleSocketStreamBuffer*  owner = reinterpret_cast<SimpleSocketStreamBuffer*>(userdata);
                std::unique_lock<std::mutex>     lock(owner->mutex);
 
                if ((!owner->empty) && (!owner->preDownload))
                {
                    // Its not bad yet.
                    // It only becomes bad if the user tries
                    // to read any of this data. Then we mark
                    // it bad. So the actual marking bad is done
                    // in underflow().
                    owner->droppedData=true;
                    // This causes the connection to close.
                    return 0;
                }
                owner->empty   = false;
                std::size_t oldSize = owner->buffer.size();
                owner->buffer.resize(oldSize + bytes);
                std::copy(ptr, ptr + bytes, &owner->buffer[oldSize]);
                owner->setg(&owner->buffer[0], &owner->buffer[0], &owner->buffer[oldSize + bytes]);
                owner->cond.notify_one();
                if (owner->sizeMarked)
                {
                    owner->sizeLeft -= bytes;
                    owner->open      = (owner->sizeLeft != 0);
                }
                return bytes;
            }
            friend size_t headFunc(char* ptr, size_t size, size_t nmemb, void* userdata)
            {
                std::size_t     bytes = size*nmemb;

                if ((bytes >= 5) && (strncmp(ptr, "HTTP/", 5) == 0))
                {
                    int   respCode  = 0;
                    char* space     = reinterpret_cast<char*>(memchr(ptr+5, ' ', bytes - 5));
                    std::string     code(space ? space : ptr, ptr+bytes);

                    if ((space != NULL) && (sscanf(&code[0]," %d OK", &respCode) == 1) && (respCode == 200))
                    {   /* GOOD */ }
                    else
                    {
                        SimpleSocketStreamBuffer*  owner = reinterpret_cast<SimpleSocketStreamBuffer*>(userdata);
                        std::unique_lock<std::mutex>     lock(owner->mutex);
                        owner->markStreamBad();
                    }
                }

                if ((bytes >=15) && (strncmp(ptr, "Content-Length:", 15) == 0))
                {   
                    SimpleSocketStreamBuffer*  owner = reinterpret_cast<SimpleSocketStreamBuffer*>(userdata);
                    std::unique_lock<std::mutex>     lock(owner->mutex);
                    std::string                      code(ptr+15, ptr+bytes);
                    owner->sizeLeft     = std::strtol(ptr+15, NULL, 10);
                    owner->sizeMarked   = true;
                    if (owner->preDownload)
                    {
                        owner->buffer.reserve(owner->sizeLeft);
                    }
                }
                return size*nmemb;
            }
            bool                    empty;
            bool                    open;
            bool                    sizeMarked;
            bool                    droppedData;
            bool                    preDownload;
            std::size_t             sizeLeft;
            std::mutex              mutex;
            std::condition_variable cond;
            std::vector<char>       buffer;
            CURL*                   curl;
            std::function<void()>   markStreamBad;
    };
 
    SimpleSocketStreamBuffer    buffer;
 
    public:
        IThorSimpleStream(std::string const& url, bool preDownload = false)
            : std::istream(NULL)
            , buffer(url, true, preDownload, [this](){this->setstate(std::ios::badbit);})
        {
            std::istream::rdbuf(&buffer);
        }
};

    }
}

#endif


