# Final *dst=*src vec copy with src in r3, dst in r4

- status: works
- tags: regalloc,inline
- scope: RPGol_802b7448
- source: fn_802B7458

symptom: r3/r4 swapped on last vec copy
cause: operator= / local ptr order
fix: inline helper copy(const V* src, V* dst) with src first
