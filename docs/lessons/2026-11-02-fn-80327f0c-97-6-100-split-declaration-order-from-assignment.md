# fn_80327F0C 97.6->100: split declaration order from assignment order of initialised float locals

- status: works
- tags: declaration-order,assignment-order,fpr,colouring,sweep,RPBow_80327F0C
- scope: RPBow_80327F0C fn_80327F0C

symptom: fn_80327F0C 97.6%: b.y in f13 not f4, k-dot f30 not f13; six-def-order sweep with initialisers capped at 97.6
cause: With initialised locals (f32 xy = ...) declaration order and evaluation order are locked together. Declaration order sets named-local colouring (first declared = highest vreg = coloured first); assignment order sets temp vreg numbers and scheduler tie-breaks. FPR allocator picks lowest free register, so each step is predictable (mwcc_dbg.sh + mwcc_sched_trace.py).
fix: Declare f32 xz, xy, yz, xm, ym, zm; on their own line, then assign in store order xy, zm, yz, xm, xz, ym. 15 declaration orders (all with xz first) and 24 assignment orders (xy<yz<xz, ym after xz) give exact. Sweep each separately (720+720), not jointly 720x720. Pitfall: asm_diff prints 'all compared functions identical' with no count on a match, so a parser expecting 'N differing lines' hides matches. mwcc_sched_trace.py scheduler.json: events kind=pass/graph/candidates/eligibility/selected, phase 0 = pre-RA, 1 = post-RA.
