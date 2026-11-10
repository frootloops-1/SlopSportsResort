# x * 0.125f const-first fmuls: write x / 8.0f

- status: works
- tags: float,fmuls
- scope: RPGol_802b1a0c
- source: fn_802B1AA4

symptom: fmuls const-first
cause: canonicalization
fix: x / 8.0f (MWCC turns into var-first multiply)
