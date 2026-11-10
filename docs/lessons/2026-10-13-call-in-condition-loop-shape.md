# Call-in-condition loop shape

- status: works
- tags: mwcc,loop
- scope: RPGol_802b614c
- source: sonnet-worker

symptom: b to call; cmpwi 0; bne body
cause: while with call in condition
fix: while ((r = fn()) != 0) { if (r == 3) return out; } return 0.0f; (for(;;)+break gave 75%)
