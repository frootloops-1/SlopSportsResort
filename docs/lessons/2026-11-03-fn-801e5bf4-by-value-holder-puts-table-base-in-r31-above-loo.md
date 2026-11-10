# fn_801E5BF4: by-value holder puts table base in r31 above loop IVs (95.9 -> 98.5); IV init addi-0 vs mr still open

- status: open
- tags: holder,vreg,regcolour,801E51B4
- scope: RPSports_801E51B4
- source: orchestrator+decomp-hard 2026-11-03

symptom: base/button-IV/names-IV permuted r29/r31/r30 vs retail r31/r30/r29; names IV init mr vs addi rX,rBase,0
cause: base is an early vreg so IVs (optimizer-created, later) colour above it; dump shows compiler substitutes global address into IV init then value numbering turns it into mr
fix: struct SelNameRef{const char** p;} base; base.p = tbl (assign, not brace-init) fixes registers (R17 ledger 117). Dead for the last 2 lines: p+i*3, const ptrs, (*)[3] view, byte offsets, struct name table, row getters, idx=i*3, shared/row counters, incremented names ptr, global direct (109), data defs moved above fn
