#include "ThorSocketStream/ThorsStream.h"
#include <iostream>
#include <string>

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

