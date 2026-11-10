# x = (v&1) ? 1 : 2 gives neg/addi

- status: works
- tags: ternary
- scope: RPGol_802b1a0c
- source: fn_802B2F90

symptom: neg/addi instead of li/clrlwi./beq
cause: ternary folding
fix: int s = 2; if (v & 1) s = 1; x = s;
