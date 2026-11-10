# ef_animcurve U8 tail key setup is a pre-RA schedule wall (same as Rotate)

- status: fails
- tags: ef_animcurve,U8,scheduling,dead-end
- scope: nw4r/ef/ef_animcurve
- source: claude/ac-u82-1029 opus

symptom: Remaining 20 lines: tail k0 r7 vs r6, target issues interp before neg0 and add k1 before or0
cause: Scheduler.c select_ready: neg releases 'or' (count 1) so it beats interp unless interp has height via a successor; webs are split before scheduling so a reused k var gives no anti-dependency
fix: dead: hoisted decls + 7 statement orders (best = baseline; k1-early orders 99.30/99.28), single reassigned k cursor 96.6, v1 in-place cursor 97.86, k0[2]->flag0 in calls 96.54 (callee-saved colours break), u32/s32 flag and u32 bool types flat. Park.
