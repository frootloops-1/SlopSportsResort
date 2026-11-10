# pf_cp932 OEM2Unicode/Unicode2OEM: pragmas, volatile, barriers, decl order, temp hoists and 10-min permuter all no gain

- status: fails
- tags: pf_cp932,permuter,pragma,regalloc,scheduling
- source: worktree /private/tmp/ogws-cp932-1028 2026-10-28

symptom: li r3,1 hoisted above the store and temp in r5 (OEM2Unicode) / non-coalesced r5 (Unicode2OEM) on the narrow-char paths; 98.53%
cause: MWCC schedules before AND after register allocation (cadmic/mwcc-debugger README): pre-RA hoist of the call-arg li makes r3 busy so RA avoids r3 for the temp. Target did not hoist; no source spelling found that changes the pre-RA schedule.
fix: Failed this round: scheduling/peephole/opt_level/global_optimizer/optimize_for_size pragmas (all regress), volatile stores, empty asm barrier (no-op), return-value local, goto common tail, lead/trail as s32/u32/src-pointer/macro exprs, decl and load order swaps, temp as u16/s32, hoisting the kana temp into i/j/new local (regress), permuter 10 min x2 (-j5): OEM2Unicode no improvement, Unicode2OEM only fuzzy-score gain from a hoist that regresses in the real diff. Next lever not yet tried: dump MWCC allocator passes with cadmic/mwcc-debugger and diff priority order against the target.
