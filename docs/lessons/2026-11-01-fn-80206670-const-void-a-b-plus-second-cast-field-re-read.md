# fn_80206670: const void* a/b plus second-cast field re-read

- status: works
- tags: constness,fn_80206670,cse,R17,RPSports
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020634c
- source: constsweep 2026-11-01

symptom: 28 lines non-const; const void* a,b -> 2 lines: original reloads 0xc(r3) in case-2 else-if, ours reloads the 0x14(r1) stack copy
cause: back-end replaces stack-copy loads with registers only when every incoming path holds the same register; IRO CSE merges p->d.fC with the earlier load
fix: const void* a/b (both needed, plain void* 89.9) and read fC through ((CtorRankView*)self)->d.fC (R17 row 47); p->d.fC is 67-73 lines worse; const self or const-typed p/q do nothing
