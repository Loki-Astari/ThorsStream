---
layout: package
generate: false
nameSpace:  ThorsAnvil::Stream
headers:
    base: ThorSocketStream
    files:
        - name:   ThorsSimpleStream.h
          functions:
            - return: 
              name:   extern
              param:  [  ]
            - return: 
              name:   "C"
              param:  [  ]
            - return: 
              name:   extern
              param:  [  ]
            - return: 
              name:   "C"
              param:  [  ]
          classes:
            - name:   SimpleSocketStreamBuffer
              parent: 
        - name:   ThorsStream.h
          functions: []
          classes:
            - name:   ThorStreamManager
              parent:  
            - name:   SocketStreamBuffer
              parent: IThorSimpleStream::SimpleSocketStreamBuffer 
children:
    - name: extern
      value: ThorSocketStream.ThorsSimpleStream.extern.md
    - name: extern
      value: ThorSocketStream.ThorsSimpleStream.extern.md
    - name: ThorStreamManager
      value: ThorSocketStream.ThorsStream.ThorStreamManager.md
    - name: "C"
      value: ThorSocketStream.ThorsSimpleStream."C".md
    - name: "C"
      value: ThorSocketStream.ThorsSimpleStream."C".md
    - name: SocketStreamBuffer
      value: ThorSocketStream.ThorsStream.SocketStreamBuffer.md
xxxx:
    - name: SimpleSocketStreamBuffer
      value: ThorSocketStream.ThorsSimpleStream.SimpleSocketStreamBuffer.md
---
