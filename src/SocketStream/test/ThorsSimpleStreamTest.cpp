#include "gtest/gtest.h"
#include "ThorsSimpleStream.h"
#include <string>
#include <cstdlib>

/*
 * Note: These test assume the file test/data/ThorStreamTest.html is available on the local web server.
 * Please install this file so it can be read from the root directory.
 *
 * Note: If the environment variable THOR_STREAM_TEST_PORT is set
 *       It will use that port on the to try and connect to the web server.
 *
 * An easy way to set this up is:
 *      brew install node.js
 *      npm install -g http-server
 *      http-server src/SocketStream/test/data/ &
 *      export THOR_STREAM_TEST_PORT=8080
 */

TEST(ThorsSimpleStreamTest, NormalOperation)
{
    char const* port = getenv("THOR_STREAM_TEST_PORT");
    port = port ? port : "80";

    std::string const schema  = "http";
    std::string const server  = "127.0.0.1";
    std::string const page    = "ThorStreamTest.html";

    std::string const url     = schema + "://" + server + ":" + port + "/" + page;

    using ThorsAnvil::Stream::IThorSimpleStream;
    IThorSimpleStream   input(url);

    std::string line;

    std::getline(input, line);
    EXPECT_EQ(line, "<html><head><title>ThorsStream Test</title></head>");

    std::getline(input, line);
    EXPECT_EQ(line, "<body>");

    std::getline(input, line);
    EXPECT_EQ(line, "    Line 1");

    std::getline(input, line);
    EXPECT_EQ(line, "    Line 2");

    std::getline(input, line);
    EXPECT_EQ(line, "</body>");

    std::getline(input, line);
    EXPECT_EQ(line, "</html>");


    // NOTE: The test data is large enough that the server will not
    //       send it in one block (see test/data/ThorStreamTest.html)
    //       as a IThorSimpleStream will underflow and set the bad bit
    //       to true because we dropped data.
    //       eof() is also correctly set.
    while(std::getline(input, line))
    {
        if (input.eof()) {
            break;
        }
    }
    EXPECT_TRUE(input.eof());
    EXPECT_TRUE(input.fail());
}

TEST(ThorsSimpleStreamTest, FullDownloadOperation)
{
    char const* port = getenv("THOR_STREAM_TEST_PORT");
    port = port ? port : "80";

    std::string const schema  = "http";
    std::string const server  = "127.0.0.1";
    std::string const page    = "ThorStreamTest.html";

    std::string const url     = schema + "://" + server + ":" + port + "/" + page;

    using ThorsAnvil::Stream::IThorSimpleStream;
    IThorSimpleStream   input(url, IThorSimpleStream::Greedy);

    std::string line;

    std::getline(input, line);
    EXPECT_EQ(line, "<html><head><title>ThorsStream Test</title></head>");

    std::getline(input, line);
    EXPECT_EQ(line, "<body>");

    std::getline(input, line);
    EXPECT_EQ(line, "    Line 1");

    std::getline(input, line);
    EXPECT_EQ(line, "    Line 2");

    std::getline(input, line);
    EXPECT_EQ(line, "</body>");

    std::getline(input, line);
    EXPECT_EQ(line, "</html>");


    // NOTE: The test data is large enough that the server will not
    //       send it in one block (see test/data/ThorStreamTest.html)
    //       but this object fetches everything into the local buffer
    //       as a result it will not fail.
    while(std::getline(input, line))
    {
        if (input.eof()) {
            break;
        }
    }
    EXPECT_TRUE(input.eof());
    EXPECT_FALSE(input.fail());
}
