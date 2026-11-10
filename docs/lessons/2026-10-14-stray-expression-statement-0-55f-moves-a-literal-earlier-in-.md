# Stray expression statement '0.55f;' moves a literal earlier in .sdata2 pool

- status: works
- tags: sdata2,pool-order
- scope: RPGol_802b5638
- source: fn_802B5808

symptom: pool literal order differs from first use
cause: pool order = creation order
fix: put 'X.Xf;' as first statement of the fn that should create it first
