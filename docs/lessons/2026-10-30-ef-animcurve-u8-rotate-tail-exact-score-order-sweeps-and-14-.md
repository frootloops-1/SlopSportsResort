# ef_animcurve U8/Rotate tail: exact-score order sweeps and 14 more shapes all <= baseline

- status: fails
- tags: ef_animcurve,U8,rotate,regalloc,dead-end
- scope: nw4r/ef/ef_animcurve AnimCurveExecuteU8, AnimCurveExecuteRotate
- source: claude/ac-tail-1030 sonnet

symptom: U8 99.58403/20 lines, Rotate 99.1673/28 lines tail key setup (k0/k1/v1 share one reg, neg0/or0 in r8)
cause: mwcc_dbg U8: v0/v1/interp have degree 126/157/309 (live through loops) so they colour first (r4/r6/r7); neg0/or0 (vreg 322/323, degree 18) colour before k0/k1 (vreg 55/58) and take r6 because v1 is not yet defined at neg0 in pre-RA order. Any source order that defines v1 before or0 (bools last, k1 early) swaps interp/v1 to r6/r7 (126-130 lines, 99.3). asm_diff line count is NOT the score: all ~150 sampled 18-line orders score 99.3 exact, use objdiff match_percent.
fix: dead: exact-% sweep of random dependency-valid orders of the 9 key-setup stmts (U8 ~1350 of 4536, Rotate ~1250; best = baseline, none above); v0=interp+8; v0 from v1; interp first (130); k1=k0+keySize (28); v1 before flag1 (20, no gain); bool as u32/static_cast/!!/no flag locals (identical); KeyIsRandom/KeyAt/KeyFlag inline helpers (identical); helper calls via k0+12/k1+12 (98.77); Rotate k1=k0+1 / keys+idx+1 (98.73), interp=v0-8 (99.157), sign0 local u8/u32, int neg0, neg0 decl moves (identical or worse)
