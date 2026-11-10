# objdiff 100% but DOL fails: check function emission order (reverse source); weak inline getter order = declaration order; delete trailing gap_ sdata2 symbol

- status: works
- tags: dol,emission-order,gap-symbol,sdata2,weak-inline
- scope: Pack/RPKernel/RPSysSystem

symptom: 47/47 objdiff exact but main.dol FAILED; sdata2 93.33 missing 4 trailing zero bytes
cause: objdiff pairs by symbol, ignoring order; gap_* symbol is alignment pad before next unit
fix: write source in exact reverse of original asm function order; reorder inline getters in class body; delete gap_*_sdata2 line from symbols.txt; reuse variables like EGG initMemory for regalloc
