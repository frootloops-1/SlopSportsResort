# Placement-new result local: declare as const pointer (T* const x = new (heap) T) to drop to lowest callee-saved rank

- status: works
- tags: regalloc,const-pointer,placement-new,coloring
- scope: Pack/RPKernel/RPSysKokeshiIcon

symptom: Construct pNglAllocator/manager swapped r30/r27
cause: new-expression result rank resists copies/helpers/decl order
fix: EGG::Allocator* const pNglAllocator = new ...; keep pHeap=pOldHeap copy; brute-force declaration-style search script printing registers works
