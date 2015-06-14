// Header only library
#include "ThorSocketStream/ThorsSimpleStream.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    namespace thor  = ThorsAnvil::Stream;

    // The IThorSimpleStream is very basic example.
    // It will download only the first block of data from the server.
    // If you try and read past the first block then it sets the badbit of the stream.
    //
    // This is specifically to keep size small and interaction fast.
    // Note: If the HTTP response is not 200 OK then the bad bit is set.
    //
    bool all = argc > 1;
    thor::IThorSimpleStream     stream("https://api.twitter.com/1.1/help/privacy.json", all);

    std::string line;
    while(std::getline(stream, line))
    {
        std::cout << line;
    }
}

