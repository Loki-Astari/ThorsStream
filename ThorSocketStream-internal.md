---
layout: package
generate: false
nameSpace:  ThorsAnvil::Stream
headers:
    base: ThorSocketStream
    files:
        - name:   1
          functions: []
          classes:
            - name:   ThorStreamManager
              parent:  
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
    - name: ThorStreamManager
      value: ThorSocketStream.1.ThorStreamManager.md
    - name: extern
      value: ThorSocketStream.ThorsSimpleStream.extern.md
    - name: "C"
      value: ThorSocketStream.ThorsSimpleStream."C".md
    - name: extern
      value: ThorSocketStream.ThorsSimpleStream.extern.md
    - name: "C"
      value: ThorSocketStream.ThorsSimpleStream."C".md
---
