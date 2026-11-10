# fn_802BBEB4 XZ distance FPR/GPR swaps

- status: open
- tags: golf,regalloc,float
- scope: RPGol_802bb608
- source: opus-worker

symptom: 99.6: lbl_804BF890/920 r3/r4 swapped; dz f2 vs f3
cause: unknown
fix: failed: VEC2Len inline, dx/dz order, sq temp, swapped terms; pointers declared first regress to 97.0. Try permuter
