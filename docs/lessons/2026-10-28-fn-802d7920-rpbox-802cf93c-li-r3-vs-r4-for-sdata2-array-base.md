# fn_802D7920 (RPBox_802cf93c) li r3 vs r4 for sdata2 array base: source shape and permuter exhausted

- status: fails
- tags: regalloc,rpbox,fn_802D7920,sda21
- scope: fn_802D7920
- source: claude/box1-1028

symptom: li r4,lbl_804C4DF0 / lfs 4(r4) where retail has r3 (2 diff lines, 99.88%)
cause: pre-RA GPR colouring of the array-base vreg; not reachable by source shape
fix: failed: scaleY local vs inline args, scaleX/scaleY locals (regress), s declared before/after M stores, pointer local for PSMTXMultVec, fn_802D9790()/fn_802D976C() inlined calls, BoxVec3 v ctor (stack layout regress), const f32 s; permuter 8 min -j6 no candidate beat base
