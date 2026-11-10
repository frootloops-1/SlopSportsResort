# Leading 0.0 in .sdata2: unused 'float zero = 0.0f;' in first-generated fn

- status: works
- tags: sdata2,pool-order
- scope: RPGol_802b7670
- source: fn_802B7770

symptom: 0.0 missing at pool start
cause: pool creation order
fix: unused float zero = 0.0f; at top of lowest-address fn
