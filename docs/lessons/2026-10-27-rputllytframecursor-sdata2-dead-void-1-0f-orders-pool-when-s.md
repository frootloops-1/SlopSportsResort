# RPUtlLytFrameCursor sdata2: dead (void)1.0f orders pool when sinit literal order disagrees with store order

- status: works
- tags: pool,sdata2,sinit,RPUtlLytFrameCursor,R17
- scope: unit

symptom: retail .sdata2 has 1.0f before 1000.0f but the sinit stores the 1000.0f global first; literals pool in codegen (emission) order
cause: a 1.0f use was created (and folded) in an earlier-emitted function; file-static const, real global ctors, store reordering do not reproduce it
fix: dead (void)1.0f; in fn_801C8744 (MATCH-PENDING R17, ledger 26); keep one named extern const defined at TU end so -C is not folded; asm_diff masks lbl_ names so check objdiff reloc diffs for pool-order
