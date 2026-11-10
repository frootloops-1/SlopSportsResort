# fn_801A2EFC: extra GPR node in pAnm inner blocks restores regs

- status: open
- tags: fn-801a2efc,RPSysSystemWinMgr,register
- source: claude 2026-10-26

symptom: natural restart() gives pMgr r28 / c1 r27 in all 4 UpdateButtonAnm copies; target is pMgr r27, c1 r30
cause: any extra GPR node inside pAnm[1]/pAnm[0] inner blocks after unbind restores exact signature; at loop top, FPR-only, or net-zero swaps do not; original likely has one coalesced mr per copy leaving no code
fix: unsolved. Dead ends: nested FrameCtrl::restart, AnmReset/AnmStart helpers, member updateButtonAnm, GetAnmFrameNum getter, named pAnmObj local, f32/s16/int local in PlayFromEnd, per-block Activate/Deactivate helpers, true vs 1; store order mFlags,mIsEnabled,mFrame gives exact regs but stores stay above conversion. Permuter needs the 4 copies hand-expanded.
