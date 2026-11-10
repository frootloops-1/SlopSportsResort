# Self copy skips r6/r7 (mr r8,r3) in tiny tail-call: r6/r7 live into the call

- status: works
- tags: regalloc,scratch,tailcall,params
- scope: Pack/RPSports/RPTnsScene/RPTns_80220994
- source: worker 2026-10-15

symptom: fn_80220BB0/BDC 99.1%: orig mr r8,r3 vs ours mr r6,r3; no r6/r7 used anywhere
cause: r6/r7 must be live up to the tail call (extra arg regs passed through); unused/unnamed params do not block regs, permuter and inline/expression/index variants all gave r6
fix: add params k,l and call the setter through a 5-arg fn-pointer cast passing (pl, s, j, k, l) -> exact; uninitialized locals hit -w err 10185
