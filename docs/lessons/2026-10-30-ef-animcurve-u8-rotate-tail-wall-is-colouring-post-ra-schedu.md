# ef_animcurve U8/Rotate tail wall is colouring + POST-RA schedule, not pre-RA

- status: open
- tags: ef_animcurve,U8,rotate,scheduling,regalloc,mwcc_dbg
- scope: nw4r/ef/ef_animcurve
- source: claude/ac-sched-1030 opus

symptom: U8 tail: target interp before neg0, add k1 before or0; k0=k1=v1=r6, neg0/or0=r8 (ours k0=interp=r7, neg0=r6, k1=r8)
cause: a post-RA scheduler runs (backend-06 vs 07 differ; blocks get flag 0x8 only in 07). Target order = post-RA schedule forced by WAR anti-deps once k1 reuses k0's r6. Pre-RA P is identical in ours. Colouring: simplify pushes ascending vreg, so codegen temps (neg0 r322/or0 r323) are coloured before named k0/k1 (r5x) and @temps (r9x-r10x); neg0 gets r6 unless v1 (early group r6) overlaps it, i.e. v1 def before or0 in P, which the list scheduler never picks (or0 count 1 > v1 count 0)
fix: open: need a source shape that changes P or makes k0/mullw2 colour before neg0. Model check: H1 (r1 before r0) only changed colours (or0->r3, mullw2->r6), as predicted
