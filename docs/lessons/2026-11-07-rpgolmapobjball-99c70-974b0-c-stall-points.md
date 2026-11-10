# RPGolMapObjBall 99C70/974B0 C++ stall points

- status: open
- tags: mwcc,cse,scheduling,golball
- scope: RPGolMapObjBall
- source: claude/golball-c-1107

symptom: 99C70: retail reloads lbl_804BF878 for the fn_80299890 arg after the loop condition loaded it; 974B0: start->p word copy load-all/store-all and GolBallBack count-before-capacity load order
cause: unknown; CSE across loop back edge in ours; inline wrappers, casts, local track pointer, for(;;) shapes, BOOL inline condition did not stop it
fix: best C: 99C70 12 diffs (IsSpecialState for output test, d.x/d.y/f.y/f.x order), 974B0 8 diffs; asm fallbacks kept
