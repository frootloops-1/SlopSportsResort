# Unrolled 10-element sum with first add folded to mr

- status: works
- tags: mwcc,loop
- source: RPGol_802b90b4

symptom: need fully unrolled sum
cause: MWCC unrolls small fixed loops
fix: plain for-loop in an inline member total()
