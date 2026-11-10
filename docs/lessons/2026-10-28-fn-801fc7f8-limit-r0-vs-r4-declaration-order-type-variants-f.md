# fn_801FC7F8 limit r0 vs r4: declaration-order/type variants flat (model explains it, no lever found)

- status: fails
- tags: regalloc,r0,fn_801FC7F8
- scope: RPSports_801fc7f8
- source: scratch worktree claude/regalloc-1028

symptom: fn_801FC7F8 limit in r4 and loaded flag in r0; target has limit in r0, flag reuses r3 (16 diff lines, 99.65)
cause: Our build colours the loaded flag (expression temp) before limit; target colours limit first
fix: failed: named flag local after limit (u32 and s32), limit declared after c, limit uninit + if/else assignment, (s32)(u32) flag cast; all stay at 16 diff lines. Second diff (add r27 vs add r3 then addi) untouched. Park.
