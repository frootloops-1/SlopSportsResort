# End-of-fn 'if (f > k) return 0; return 1;' gives mfcr/cntlzw

- status: works
- tags: compare,bool
- scope: RPGol_802b1a0c
- source: fn_802B439C

symptom: setcc instead of branches
cause: MWCC setcc conversion
fix: static inline int gt(a,b){ if (a > b) return 1; return 0; } then if (gt(..)) return 0; return 1;
