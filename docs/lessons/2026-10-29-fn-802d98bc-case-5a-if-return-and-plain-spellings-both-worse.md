# fn_802D98BC case 5a: if-return and plain && spellings both worse

- status: fails
- tags: fn_802D98BC,RPBox_802cf93c,regalloc
- scope: RPBox_802cf93c
- source: claude/box802cf-r2-1029 opus

symptom: 5a result r27 vs target r23 (58 lines)
cause: 5a must be an @inline var coloured after 5b..5e; the ternary gives a codegen temp
fix: failed: if (...) return TRUE; return FALSE; (94.8), plain && (98.6, zeros become mr copies)
