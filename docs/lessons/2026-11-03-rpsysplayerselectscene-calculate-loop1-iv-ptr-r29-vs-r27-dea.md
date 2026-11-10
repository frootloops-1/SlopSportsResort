# RPSysPlayerSelectScene Calculate loop1 IV ptr r29 vs r27: dead ends

- status: fails
- tags: regalloc,induction,RPSysPlayerSelectScene
- scope: Pack/RPSports
- source: claude opus worker 2026-11-03

symptom: Last 8 lines: loop1 strength-reduced &info+4i pointer gets r29, target r27 (coloured after p710 in target)
cause: unknown: the IRO IV ranks above p710 in ours; mwcc_dbg panics (retrowin32 256MB 'not enough memory reserved') on this TU even trimmed, so no vreg dump
fix: Dead (all identical 8 lines): i at Calculate top, info/i at Calculate top, i/info decl order, p710 declared before loop1 (assigned in loop), loop1 in braces, while-loop, ++i, separate j (after i), named mii in loop1, pInfo=&info, MiiAt/ChanAt ref accessors, SetMii/SetChan inline setters, *(arr+i). Worse: s32 j before i / for(s32 i) both loops (18), static inline FillInfo(&info,p) (21), named pp/pc pointers (10)
