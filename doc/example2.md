[![endorse](http://api.coderwall.com/lokiastari/endorsecount.png)](http://coderwall.com/lokiastari)
[![Build Status](https://travis-ci.org/Loki-Astari/ThorsStream.svg?branch=master)](https://travis-ci.org/Loki-Astari/ThorsStream)

![ThorStream](../img/stream.jpg)

###Example Usage
An alternative version of the class can be used. This will download the data asynchronously in the background. If you run out of data the stream will block the main thread while more data is retrieved. But since the download is asynchronous it is unlikely to stop unless this is a real slow connection. The background thread buffers up data until the stream has an underflow then sets the data as the source.

````c++
    // Asynchronous download of data.
    // Requires you to link against ThorSocketStream14.so (or whatever platform extension for shared libraries).
    //
    #include "ThorSocketStream/ThorsStream.h"

    int main()
    {
        namespace thor  = ThorsAnvil::Stream;

        // The IThorStream downloads data asynchronously in the background.
        thor::IThorStream     stream("https://api.twitter.com/1.1/help/privacy.json");

        std::string line;
        while(std::getline(stream, line))
        {
            std::cout << line;
        }
    }
````



