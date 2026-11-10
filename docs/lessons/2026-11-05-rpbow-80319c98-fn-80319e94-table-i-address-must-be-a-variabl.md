# RPBow_80319C98 fn_80319E94: table [i] address must be a variable coloured after the base

- status: works
- tags: RPBow,regalloc,table-lerp,GPR,mwcc_dbg,R17
- scope: Pack/RPSports/RPBowScene/RPBow_80319C98

symptom: base g (lbl->p4) and index i GPRs swapped vs target; insensitive to decl order/types/helpers
cause: mwcc_dbg dump: g,i are named vars; the [i] address add (g + i<<2) is a TEMP because the CSE var holds +0x1494 and is folded away, so it colours before g and takes the lowest reg; target colours g first
fix: R17: BowExcelGlobal* gi = (BowExcelGlobal*)((f32*)g + i); read gi->t1494[0]; declare g (uninitialised) before i -> 0 diffs (ledger 250). Same trick on BowCamShake (fn_8031B3F4) did not close: i*12 and lbl load are temps there too
