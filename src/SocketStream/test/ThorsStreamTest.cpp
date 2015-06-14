#include "gtest/gtest.h"
#include "ThorsStream.h"
#include <string>
#include <cstdlib>

/*
 * Note: These test assume the file test/data/ThorStreamTest.html is available on the local web server.
 * Please install this file so it can be read from the root directory.
 *
 * Note: If the environment variable THOR_STREAM_TEST_PORT is set
 *       It will use that port on the to try and connect to the web server.
 */

TEST(ThorsStreamTest, NormalOperation)
{
    char const* port = getenv("THOR_STREAM_TEST_PORT");
    port = port ? port : "80";

    std::string const schema  = "http";
    std::string const server  = "127.0.0.1";
    std::string const page    = "ThorStreamTest.html";

    std::string const url     = schema + "://" + server + ":" + port + "/" + page;

    using ThorsAnvil::Stream::IThorStream;
    IThorStream   input(url);

    std::string line;
    while(std::getline(input, line))
    {
        std::cout << "L:" << line << "\n";
    }
}

