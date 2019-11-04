---
layout: class
generate: false
typeInfo:
    namespace: ThorsAnvil::Stream
    header:    ThorSocketStream/ThorsSimpleStream.h
    classname: SimpleSocketStreamBuffer
    parent:    
    template:  
    description: 
    methods:
        - return: ' '
          name: 
          param: [  ' // // Constructs an std::istream object that streams data from the given url. // Uses curl underneath the hood to retrieve the data. // // A read from a stream with no more data (even if it is not all the data will cause an error. // If you need to gurantee you get all the data then use `IThorStream`. IThorSimpleStream(std::string const& url', ' ReadStraergy readStrat = OneBlock) : std::istream(nullptr) ', ' buffer(url', ' EasyCurl', ' readStrat', ' [this](' ]
          mark:  
        - return: ''
          name: //
          param: [  ]
          mark: 
    protected: []
    virtual: []
children:
    - name: 
      value: ThorSocketStream.ThorsSimpleStream.SimpleSocketStreamBuffer.methods.1..md
    - name: //
      value: ThorSocketStream.ThorsSimpleStream.SimpleSocketStreamBuffer.methods.//.//.md
---
