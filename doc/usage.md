[![Build Status](https://travis-ci.org/Loki-Astari/ThorsStream.svg?branch=master)](https://travis-ci.org/Loki-Astari/ThorsStream)

![ThorStream](../img/stream.jpg)


## ThorsAnvil::Stream::IThorSimpleStream

````
    Defined in:     ThorsSocketStream/ThorsSimpleStream.h
    Interface:      std::istream
    libraries:      -lcurl
    Constructor:
        IThorSimpleStream(std::string const& url, bool preDownload = false)

            url:            The url (including schema) of a web resource.
            preDownload:    false:      Reads the first block from the socket created
                                        into a local buffer.
                            true:       Reads the whole file into a local buffer.

    Description:
        Any response from the server that is not a "200 OK" results in the badbit being set.
        and the buffer being empty.

        if preDownload is false an attempt to read past the end of the buffer result in
        the badbit being set.


    Defined in:     ThorsSocketStream/ThorsStream.h
    Interface:      std::istream
    libraries:      -lThorSocketStream14 -lcurl
    Constructor:
        IThorStream(std::string const& url)

            url:            The url (including schema) of a web resource.

    Description:
        This creates a background stream manager thread. Note this is only one
        stream thread manager for all IThorStream objects and it is only created
        once when the first IThorStream object is constructors.

        The stream manager will download data from the web servers. Note: it only
        uses a single thread a multiplexes across the open sockets reading data into
        each individual bucket.

        If read operation finds a buffer empty it will block (stall) the reading
        thread until more data is available.
````





