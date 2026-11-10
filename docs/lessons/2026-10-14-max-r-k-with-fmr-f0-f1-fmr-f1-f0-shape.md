# max(r,K) with fmr f0,f1; fmr f1,f0 shape

- status: works
- tags: float,compare
- scope: RPGol_802b5638
- source: fn_802B58D8

symptom: cror or different branch
cause: ternary form
fix: static inline GolMax(a,b){ return a < b ? b : a; }
