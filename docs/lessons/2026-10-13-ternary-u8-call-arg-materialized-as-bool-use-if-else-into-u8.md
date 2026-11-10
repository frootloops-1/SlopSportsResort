# Ternary u8 call arg materialized as bool; use if/else into u8 local

- status: works
- tags: mwcc,ternary,args
- scope: RPGol_802bb608
- source: opus-worker

symptom: c ? 0 : p->u8 became li 1/cmpwi
cause: ternary promoted to bool
fix: u8 v; if (c) v = 0; else v = p->field; f(v)
