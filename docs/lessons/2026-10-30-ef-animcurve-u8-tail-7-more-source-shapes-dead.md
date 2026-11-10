# ef_animcurve U8 tail: 7 more source shapes dead

- status: fails
- tags: ef_animcurve,U8,dead-end
- scope: nw4r/ef/ef_animcurve AnimCurveExecuteU8
- source: claude/ac-sched-1030 opus

symptom: U8 20 lines tail key setup
cause: each changes colour numbering or CSE, not the pre-RA P
fix: dead: r1 computed before r0 (18 lines but 99.58->99.3), t computed after key setup (93.1), k0 shared with function-scope found-path 'values' (no change, k0 becomes @temp r93), k0 as inline keys+idx*keySize exprs + flag0 in calls (516 lines), interp declared right after k0 (130), v1 before flag1 + bools last (126), v1 in-place cursor from k1 base + flag1 in calls (264)
