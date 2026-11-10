# fn_802BE034: shared function-scope int i, const void* param copy, compare-chain spelling

- status: works
- tags: loop-counter,const,compare-fold,fn_802BE034,R17,RPGol
- scope: Pack/RPSports/RPGolScene/RPGol_802bdd70
- source: wave3 2026-11-01

symptom: 98.4%, 3612 bytes: slot-loop i/vis vs pointer colouring, res load order, anm pointer register, cmplwi range test
cause: x==0||x==1||x==2 folds 1..2 into subi/cmplwi; a function-scope int i reused by several loops is split into one temporary per loop with high register numbers; const pointee alias safety comes from the pointer param's DECLARED type (a const local copy of a non-const param does not help)
fix: !(res->s34 && res->s34 != 1 && res->s34 != 2) gives the cmpwi chain; one shared int i for restart/state-5/slot loops (ball block own i, n = s34==2 ? 5 : 10); b2F5/b2F6 bool; base+plural inline; const void* resArg + static_cast copy (R17 row 73); GolPlayEnd (R17 row 74). Dead: enum/bool ternary for vis, named slot pointer local, slot-loop body as static inline, map local variants, reference param. color_sim rule: lowest-numbered free register among those already allocated, else next callee-saved from r31 down; a sim plus permutation search found the ordering quickly
