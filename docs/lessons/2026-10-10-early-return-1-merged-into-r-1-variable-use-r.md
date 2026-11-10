# Early return 1 merged into r=1 variable: use r++

- status: works
- tags: mwcc,return,merge,regalloc
- scope: RPGolDrawManager

symptom: orig early return li r3,1; b epilogue, ours li r31,1; b mr r3,r31 (fn_80294590 99.1)
cause: MWCC merges return-constant into a local assigned the same literal constant elsewhere
fix: assign the local non-literally (s32 r=0; ... r++;) so the constant differs at merge time; r=2 probe confirmed
