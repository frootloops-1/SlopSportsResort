# fn_8027D400 (RPBsb_8027d3ec): reloaded .sdata limit gets f2 not f0 even as an inline param

- status: fails
- tags: regalloc,fpr,inline
- scope: RPBsb_8027d3ec fn_8027D400
- source: FPR batch 2 2026-10-28

symptom: 99.34; adds to the earlier recorded failure
cause: nested-inline temps outrank an outer inline param, so lim is coloured after the += temps; its load must precede the pos stores (possible alias)
fix: none: BsbSlotAdvance(s,d,f32 lim) inline 97.2 (bool return adds mfcr), single-def lim identical, comma-expression adds identical
