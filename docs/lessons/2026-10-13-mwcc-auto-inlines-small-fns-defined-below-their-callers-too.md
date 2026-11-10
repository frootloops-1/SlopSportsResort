# MWCC auto-inlines small fns defined BELOW their callers too

- status: works
- tags: mwcc,inline
- source: RPGol_802b90b4

symptom: callers dropped 98->0 after adding a small fn below them
cause: deferred codegen lets MWCC inline later-defined fns
fix: wrap the small fn in #pragma auto_inline off / #pragma auto_inline reset
