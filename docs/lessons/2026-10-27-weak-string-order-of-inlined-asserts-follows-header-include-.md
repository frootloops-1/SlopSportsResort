# Weak @STRING@ order of inlined asserts follows header include/definition order

- status: works
- tags: data,weak,strings,order,egg
- scope: egg/gfxe/eggModelBoundingInfo
- source: mbi-1027

symptom: @STRING@ objects in .data reversed vs retail (ours setSphere,setAABB,getLocalMtx; retail getLocalMtx,setAABB,setSphere)
cause: order depends on parse/definition order of the inline functions containing the asserts, including which header is included first
fix: move #include eggModelEx.h to after the ModelBoundingInfo class (forward-declared ModelEx), and define setAABB before setSphere -> .data 100%
