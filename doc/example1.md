[![endorse](http://api.coderwall.com/lokiastari/endorsecount.png)](http://coderwall.com/lokiastari)
[![Build Status](https://travis-ci.org/Loki-Astari/ThorsStream.svg?branch=master)](https://travis-ci.org/Loki-Astari/ThorsStream)

![ThorStream](../img/stream.jpg)

###Example Usage
Simple easy to use stream library that does HTTP.

````c++
    // Header only library
    #include "ThorSocketStream/ThorsSimpleStream.h"
    #include <iostream>
    #include <string>

    int main()
    {
        namespace thor  = ThorsAnvil::Stream;

        // The IThorSimpleStream is very basic example.
        // It will download only the first block of data from the server.
        // If you try and read past the first block then it sets the badbit of the stream.
        //
        // This is specifically to keep size small and interaction fast.
        // Note: If the HTTP response is not 200 OK then the bad bit is set.
        //
        thor::IThorSimpleStream     stream("https://api.twitter.com/1.1/help/privacy.json");

        std::string line;
        while(std::getline(stream, line))
        {
            std::cout << line;
        }
    }
````

The first version is designed for speed and ease of use. The cost is that it may not always work. There is an extra parameter to the constructor that forces the stream to download all data during construction. This prevents problems when you have larger downloads. The cost is that you have to download all the data during construction of the object.

````c++
    // Header only library
    #include "ThorSocketStream/ThorsSimpleStream.h"

    int main()
    {
        namespace thor  = ThorsAnvil::Stream;

        // The IThorSimpleStream is very basic example.
        // By passing true as the second parameter to the constructor you force the object to download the whole content of the file.
        //
        // This may result in slower usage if you have a big file.
        //
        thor::IThorSimpleStream     stream("https://api.twitter.com/1.1/help/privacy.json", true);

        std::string line;
        while(std::getline(stream, line))
        {
            std::cout << line;
        }
    }
````

