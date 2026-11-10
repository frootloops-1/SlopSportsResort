# fn_801EF4B8: n-- before the second curve loop gives retail's second-loop colours (last2 shares n's register); first-loop last still open

- status: open
- tags: regalloc,color_sim,two-webs,RPSports_801ef064
- scope: Pack/RPSports/RPSportsCommon/RPSports_801ef064
- source: claude/sp801ef-1103

symptom: retail second loop subi r30,r30,1 / xoris r28 (bound shares n's register); first loop last r28/col r27/xor r26 vs ours r26/r28/r27; j r26 vs r25
cause: a named variable's second web is numbered above the locals: n-- makes the second-loop bound a late web of n (99.5 -> 99.6, 48 -> 42 lines). color_sim: first-loop last (named, vreg 37) must be numbered above the loop temps (xor 55, col word 56); no degree change reaches it
fix: FAILED for the first loop: decl permutations (last/col/i, j at top), col r/g/b/a order (24), last assigned twice, last inside the loop, i<=n-1 condition, no named last (CSE keeps n-1 live), loop in an inline helper with last param (105 lines)
