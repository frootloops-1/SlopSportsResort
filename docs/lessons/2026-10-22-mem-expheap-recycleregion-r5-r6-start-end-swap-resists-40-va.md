# mem_expHeap RecycleRegion_ r5/r6 start/end swap resists ~40 variants

- status: fails
- tags: regalloc,mem_expHeap,RecycleRegion_

symptom: 99.2%: tail loads freeRegion.start into r6 and end into r5; original is end=r6 first, start=r5 (mblock)
cause: MWCC gives the subtrahend of the size-check subtraction the first load / r6. Writing start-end flips the tail to match but is wrong semantics
fix: No correct-semantics form found: local temps, casts, GetUIntPtr one side, +0 wrappers, negation, struct-copy init, FillFreeMemory_ stub, decl order, array/&start, const MemRegion* helper params (worse) all fail. Permuter stand-in does not reproduce it (base 9000). Do not repeat.
