# fn_802C698C: IRO holder-struct trick cannot work when the competing temp is a back-end codegen vreg (int-to-float lha/xoris r97/r98)

- status: fails
- tags: rpgol,802c698c,vreg,backend,iro,nogain
- source: worker iro-698c 2026-10-31

symptom: 99.8%: n r3 / conversion r0 vs target n r0 / conversion r3
cause: named locals r32-39 and IRO @temps r40-51 are always below back-end codegen vregs (lha r97, xoris r98, lis r99); colour order is descending vreg within sweep 1, so n can only be coloured before the conversion if n is itself a back-end temp created after the conversion
fix: Check mwcc_dbg numbering before trying IRO-level steering. Split float temp (f32 f = a->mFrameCtrl.mStartFrame; s->idx = arg->idx; mFrame = f; mFlags = 0; start();) gives retail registers exactly (99.0) but issues stw s->idx after lfd instead of after sth (pointer stores keep order in Scheduler.c). Dead: GolIdxRef holder (flat), inline getter incl. volatile (n @temp r48), local int n[1] (IRO scalarizes), s->idx = GolRestart(a, arg->idx) (99.7), split float temp + named n (99.7). COpt_ArrayToRegister makes late vregs only after full unrolling. Untried: a single-expression form defining n as back-end temp between conversion and stores (would be R17).
