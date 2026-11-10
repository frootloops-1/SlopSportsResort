# TBuffer: define allocate/allocate/onAllocate out of class to push weak virtuals to TU tail

- status: works
- tags: eggController,TBuffer,weak-order,template
- scope: egg/core/eggController
- source: claude/controller-1027

symptom: In-class TBuffer virtuals allocate(Fii)/onAllocate were emitted right after the Mgr ctor (direct refs), orig emits all six at the TU tail in vtable order (eCoreDevType group, then PCC group)
cause: In-class inline virtuals referenced from a function are queued after it; out-of-class template member definitions are instantiated at end of TU
fix: Declare in class, define after class in eggBuffer.h: allocate(int,int), allocate(int,Heap*,int), onAllocate. DOL diff 1893 -> 294. Also learned: checkRange @STRING pools are emitted in reverse order of first checkRange expansion (LIFO); in-class virtual dtors are queued eagerly after the first function referencing the vtable; out-of-class dtors go to tail (orig keeps dts early, after errRange<eCDT>)
