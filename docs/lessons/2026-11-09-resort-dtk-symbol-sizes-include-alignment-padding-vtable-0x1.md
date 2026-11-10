# resort: dtk symbol sizes include alignment padding (vtable 0x10 vs 0xC, float 8 vs 4) and block unit_cmp 100%

- status: works
- tags: resort,symbols,vtable,size
- scope: resort
- source: RP batch 4 (2026-11-09)

symptom: unit_cmp .data/.sdata2 below 100 with all code exact
cause: dtk sizes objects up to the next aligned object
fix: set the symbols.txt size to the real emitted size
