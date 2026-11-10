# Compare into bool local gives mfcr+srwi. form

- status: works
- tags: mwcc,float,compare
- scope: RPGol_802b66c4
- source: opus-worker

symptom: need mfcr/srwi. after fcmpo
cause: bool temp materialized
fix: bool in = a*a < b*b; if (in)
