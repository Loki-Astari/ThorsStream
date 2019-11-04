---
layout: class
generate: false
typeInfo:
    namespace: ThorsAnvil::Stream
    header:    ThorSocketStream/ThorsStream.h
    classname: SocketStreamBuffer
    parent:    IThorSimpleStream::SimpleSocketStreamBuffer
    template:  
    description: 
    methods:
        - return: ' '
          name: 
          param: [  ' // // A background thread reads the data from the URL. // reading from the stream when no data is available will cause the read to block // until data has been retrieved and is now available. // // Multiple IThorStream objects will use the same thread to download data as we are // using the curl multi handle to handle all the connections simultaneously. IThorStream(std::string const& url) : std::istream(NULL) ', ' buffer(url', ' [this](' ]
          mark:  
        - return: ''
          name: //
          param: [  ]
          mark: 
    protected: []
    virtual: []
children:
    - name: X
      value: ThorSocketStream.ThorsStream.SocketStreamBuffer.methods.1.2.md
    - name: Y
      value: ThorSocketStream.ThorsStream.SocketStreamBuffer.methods.1.2.md
---
