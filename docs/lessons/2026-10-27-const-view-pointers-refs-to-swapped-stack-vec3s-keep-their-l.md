# Const view pointers/refs to swapped stack VEC3s keep their loads live across later local stores

- status: works
- tags: mwcc,cse,const,swap,RPUtlCollisionChecker,fn_801BC854
- scope: Pack/RPUtility/RPUtlCollisionChecker

symptom: after a VEC3 swap (struct copy forces stack), ours reloads start/end from stack after storing another local VEC3; target loads them once and keeps them in f2-f5 (78%)
cause: stores to an address-taken local kill loads from other address-taken locals unless read through a const pointer/ref
fix: const VEC3* s = &start, *e = &end; after the swap and read through them: 78.3 -> 97.9; field-wise start/end/hit assignment and direct dot expressions (not the Dot inline, whose return temp gets copy-propagated into the f32 swap) -> 99.4
