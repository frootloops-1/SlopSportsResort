# Weak inline on wrong side (DOL order): plain static helper calling it, defined between, auto-inlined

- status: works
- tags: weak-inline,emission-order,static-helper,dol
- scope: Pack/RPKernel/RPSysTagProcessor

symptom: objdiff 100 all sections but DOL fails 443 bytes; weak GetTextColor emitted after caller
cause: weak emission point is the first referencing function slot
fix: non-inline file-static helper (anon ns) calling the weak fn, defined in source between caller and the function it should follow; MWCC inlines it, linker strips standalone, weak emission moves to helper slot. Also helper w/ ctx ptr param for stack slots; *(u8*)((u32)mgr->arr+idx) address form fixes add reg swap
