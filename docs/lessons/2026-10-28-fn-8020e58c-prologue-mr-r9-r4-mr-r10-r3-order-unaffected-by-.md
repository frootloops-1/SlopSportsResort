# fn_8020E58C: prologue mr r9,r4 / mr r10,r3 order unaffected by declaration order or const self

- status: fails
- tags: fn_8020E58C,RPSports_8020b294,prologue,schedule
- scope: RPSports_8020b294
- source: claude/sports3-1028 sonnet

symptom: target li r28;li r8;mr r9,r4;mr r10,r3;li r7 vs ours mr hoisted earlier
cause: unknown; scheduling of the loop-invariant row pointer copies
fix: failed: s/d decl order in loop (96.3), dst before src (96.1), count/last swap (96.4), count/last after limit (unchanged), SelView* const self (unchanged). Parked; tooling note: git checkout <file> is denied for workers, keep a scratch copy
