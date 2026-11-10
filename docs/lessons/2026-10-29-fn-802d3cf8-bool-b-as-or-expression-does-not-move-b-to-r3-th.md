# fn_802D3CF8: BOOL b as || or !(&&) expression does not move b to r3; the if-assign form is closest

- status: fails
- tags: fn_802D3CF8,RPBox_802cf93c,regalloc,bool,elor
- scope: RPBox_802cf93c
- source: claude/box802cf-r5-1029 opus

symptom: retail b (BOOL b = TRUE; if (w70 != 1 && w2D4 == 1) b = FALSE) sits in r3 and the in.flags temp in r4; ours b r6 / flags r3 (mwcc_dbg: b is named local r36 coloured after the expression temps)
cause: b needs a higher colouring rank than the in.flags CSE temp; the ELOR result temp changes the block shape instead (li 0 / li 1 order)
fix: failed: BOOL b = w70 == 1 || w2D4 != 1 (same score, different shape), BOOL b = !(w70 != 1 && w2D4 == 1) (235 diff lines). Remaining 99.3 residue: b r3/r6, h r10/r9, BoxLerpABT FPR order, w680 reload regs, sign block FPRs
