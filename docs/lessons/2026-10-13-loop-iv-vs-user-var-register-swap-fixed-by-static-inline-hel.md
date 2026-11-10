# Loop-IV vs user var register swap fixed by static inline helper

- status: works
- tags: mwcc,regalloc,loop,inline
- scope: RPGol_802bf4f8
- source: opus-worker

symptom: fn_802C0518 msgIdx r26 vs loop IV r27 swapped; 120 declaration orders failed
cause: allocation order of user var vs induction var
fix: compute the value via a static inline helper returning it
