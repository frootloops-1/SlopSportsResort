# fn_801A2EFC: second counter j merged into i for u8 loops; hoisted const 1 colored r27 vs r30

- status: fails
- tags: regalloc,winmgr,2EFC,second-counter,u8-loop
- scope: Pack/RPKernel/RPSysSystemWinMgr

symptom: 99.5, natural restart() 98.5
cause: tracked u8 loops give const-1 last; untracked loops (u8 do-while, i+=1) give right colors but add clrlwi
fix: unsolved after 2 sessions; run permuter on register signature or find a matching u8-loop with hoisted const 1 in another TU
