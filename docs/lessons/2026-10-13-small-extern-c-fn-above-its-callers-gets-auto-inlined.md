# Small extern C fn above its callers gets auto-inlined

- status: works
- tags: mwcc,inline
- source: RPGol_802b90b4

symptom: callers show stb instead of bl
cause: MWCC auto-inlines small earlier-defined fns
fix: wrap its definition in #pragma auto_inline off / #pragma auto_inline reset
