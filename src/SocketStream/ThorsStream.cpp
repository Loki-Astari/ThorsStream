
#include "ThorsStream.h"
#include <unistd.h>

using namespace ThorsAnvil::Stream;


// Of OK is not true then the object
// will have thrown an exception so its
// its not safe to do anything but return
// immediately
void IThorStream::ThorStreamManager::eventLoop(bool ok)
{
    // If multi failed to initialize in the constructor
    // There is no point in continuing the thread.
    if (!ok)
    {   return;
    }

    // Can not let an exception escape a thread.
    // If it did it would cause the application
    // to terminate.
    try
    {
        std::unique_lock<std::mutex> lock(mutex);
        while(!finished)
        {
            // 1: Get the File descriptors that curl has ready.
            int     max_fd  = 0;
            fd_set  read;
            fd_set  writ;
            fd_set  exec;
                
            FD_ZERO(&read);
            FD_ZERO(&writ);
            FD_ZERO(&exec);

            CURLMcode   result  =  curl_multi_fdset(multi, &read, &writ, &exec, &max_fd);
            if (result != CURLM_OK) {throw std::runtime_error("curl_multi_fdset: Failed");}

            if (max_fd == 0)
            {
                // No file descriptors.
                // There is no point doing anything.
                // So wait until a new curl easy object is added.
                // Then re-start the loop.
                cond.wait(lock);
                continue;
            }

            // 2: Calculate the timeout we can use in select/poll
            timespec timeoutSpec = {0,0};
            if (max_fd == -1)
            {
                // curl special case.
                // We need to call curl_multi_perform() soon
                // so use a 100 millisecond timeout
                timeoutSpec.tv_sec  = 0;
                timeoutSpec.tv_nsec = 100 * 1000000;    // convert milli to nano
            }
            else
            {
                long timeout;
                result = curl_multi_timeout(multi, &timeout);
                if (result != CURLM_OK) {throw std::runtime_error("curl_multi_timeout: Failed");}
                if (timeout == -1)
                {   timeout = 300;
                }

                timeoutSpec.tv_sec  = timeout/1000;
                timeoutSpec.tv_nsec = timeout%1000 * 1000000; // convert milli to nano
            }

            // 3: Wait for activity on any of the file descriptors.
            int count;
            do
            {
                lock.unlock();
                count = pselect(max_fd+1, &read, &writ, &exec, &timeoutSpec, NULL);
                lock.lock();
            }
            while ((count == -1) && (errno == EINTR));
            if (count == -1) {throw std::runtime_error("pselect: Failed");}

            // 4: Handle all the CURL calllback routines.
            int running_handles;
            do
            {
                result = curl_multi_perform(multi, &running_handles);
            }
            while(result == CURLM_CALL_MULTI_PERFORM);
            if (result != CURLM_OK) {throw std::runtime_error("curl_multi_perform: Failed");}

            // 5: Handle all the messages generated by curl.
            //    Currently this is simply the fact that a stream has closed.
            CURLMsg*    message;
            int         msgs_in_queue;
            while((message = curl_multi_info_read(multi,  &msgs_in_queue)) != NULL)
            {
                if (message->msg == CURLMSG_DONE)
                {
                    CURL* easy = message->easy_handle;
                    char* priv;
                    if (curl_easy_getinfo(easy, CURLINFO_PRIVATE, &priv) == CURLE_OK && priv != NULL)
                    {
                        IThorStream::SocketStreamBuffer* owner = reinterpret_cast<IThorStream::SocketStreamBuffer*>(priv);
                        owner->markAsDone();
                    }
                }
            }
        }
    }
    catch(std::exception const& e)
    {
        // Log error:
        std::cerr << "Exception in Thread:\n\t" << e.what() << "\n";
    }
    catch(...)
    {
        // Log error:
        std::cerr << "Exception in Thread:\n\tUNKNOW (...)\n";
    }
    // Ignore error
}


