# (x-9)<=3 subi/cmplwi range test

- status: works
- tags: compare
- scope: RPGol_802b1a0c
- source: fn_802B2F90

symptom: two cmpwi
cause: x >= 9 && x <= 12
fix: (u32)(x - 9) <= 3
