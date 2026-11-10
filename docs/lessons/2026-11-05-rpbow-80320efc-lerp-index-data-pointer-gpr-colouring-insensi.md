# RPBow_80320EFC lerp index/data-pointer GPR colouring insensitive to inline shape

- status: fails
- tags: RPBow_80320EFC,fn_8032212C,fn_80320EFC,lerp,regalloc
- scope: unit

symptom: lerp i r5/r3 vs r4; data pointer d coloured after index shift (target colours d first, d in r3/r0)
cause: unknown: target behaves as if d were a newer temp than i<<2
fix: none. Dead: i types (long/s32 give i r4 but fold i+1 into lfs offset), d types const/void*/u32/f32*, uninit decl perms of i/t/d, d as inline param (either order), d loaded before compare, no-d (CSEs tbl2 base -> lfsx), level-2 BowData() getter; c as vel ctor arg expression; mwcc_dbg dump never got the port-9001 lock in 30 min
