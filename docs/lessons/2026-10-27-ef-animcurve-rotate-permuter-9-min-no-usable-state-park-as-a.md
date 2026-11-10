# ef_animcurve Rotate permuter 9 min no usable state, park as allocation wall

- status: fails
- tags: ef_animcurve,rotate,permuter
- scope: nw4r/ef/ef_animcurve
- source: worker a2e935f4, 2026-10-27

symptom: Rotate 98.5%, region A k0+0xc/k1 reg and region B add order/random0 reg
cause: register-allocation wall; permuter never touches either residue
fix: dead: permute.py --static, -j 9, ~4650 iters, score 1625->1600 only via semantics change rb=(ra+=2); same-meaning state !(flag1!=0) regresses verify diff lines. Permuter gains on large stand-ins do not carry over; apply states to the target fn only (sed hits U8/F32 copies)
