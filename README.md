[![Build Status](https://travis-ci.org/Loki-Astari/ThorsStream.svg?branch=master)](https://travis-ci.org/Loki-Astari/ThorsStream)
[![codecov.io](http://codecov.io/github/Loki-Astari/ThorsStream/coverage.svg?branch=master)](http://codecov.io/github/Loki-Astari/ThorsStream?branch=master)  
[![Code Review](http://www.zomis.net/codereview/shield/?qid=38455)](http://codereview.stackexchange.com/q/38455/507)
[![Code Review](http://www.zomis.net/codereview/shield/?qid=38402)](http://codereview.stackexchange.com/q/38402/507)


![ThorStream](img/stream.jpg)

An socket library that treats a socket like a regular io-stream.

* [Simple Example](doc/example1.md)
* [Bigger Example](doc/example2.md)
* [Building](doc/building.md)
* [Documentation Usage](doc/usage.md)
* [Documentation Internal](doc/internal.md)

### Testing

When building this library it will automatically run the unit tests. The unit test require that the files in "src/SocketStream/test/data/" can be retireved via http requests. If you have have a web server up and running this is simple just link the directory to your web root. If you don't have one installed the easiest way is to use npm to install a simple http-server:

    sudo apt-get install npm -y
    npm install -g http-server
    http-server src/SocketStream/test/data/ &

