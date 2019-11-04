---
layout: package
generate: false
nameSpace:  ThorsAnvil::Stream
headers:
    base: ThorSocketStream
    files:
        - name:   ThorsSimpleStream.h
          functions: []
          classes:
            - name:   IThorSimpleStream
              parent: std::istream 
        - name:   ThorsStream.h
          functions: []
          classes:
            - name:   IThorStream
              parent: std::istream 
children:
    - name: IThorSimpleStream
      value: ThorSocketStream.ThorsSimpleStream.IThorSimpleStream.md
    - name: IThorStream
      value: ThorSocketStream.ThorsStream.IThorStream.md
---
