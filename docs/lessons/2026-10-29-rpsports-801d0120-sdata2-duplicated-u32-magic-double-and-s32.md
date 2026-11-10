# RPSports_801D0120 sdata2: duplicated u32 magic double and S32-after--1 not reproduced

- status: fails
- tags: sdata2,pool-order,magic-double
- scope: RPSports_801D0120
- source: claude/w-buttona-data-1029

symptom: target pool 0f 1f -1 S32dbl 0.5 U32dbl' (two separate u32 doubles); ours dedups u32 and puts S32 before -1
cause: unknown; @NNNN numbers say S32 is created before fn_801D017C and the second u32 double right after it
fix: dead ends: full deferred descending source, immediate 017C + deferred rest (breaks text order), static inline helper for frame=start, calling 017C from 09B0; no change to pool order
