# Tiny map-object subclass: hand extern C void*[4] vtable named lbl_ + local struct; ctor returns self

- status: works
- tags: rpgolmapobjtee,vtable,ctor
- scope: RPGolMapObjTee
- source: sonnet

symptom: need class vtable .data
cause: no real virtuals needed
fix: extern C void* lbl_803C7908[4]={0,0,(void*)fn,0}; local struct with vtbl at 0, descending-order defs
