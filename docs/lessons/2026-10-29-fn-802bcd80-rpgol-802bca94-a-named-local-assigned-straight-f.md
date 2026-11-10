# fn_802BCD80 (RPGol_802bca94): a named local assigned straight from an inline's return merges into the inline's high result temp; do part of the work in the caller

- status: works
- tags: RPGol_802bca94,regalloc,mwcc_dbg,inline
- scope: RPGol

symptom: 99.67%: pure swap r30<->r31 between idx and v
cause: GolWorkScore clamped the score inside the inline, so v folded into the inline's result temp (r40) which is numbered above idx (r37) and was coloured first, taking r31. Target gives r31 to idx.
fix: Inline returns the raw score; the clamp (if v<0 v=0 else if v>1000 v=1000) is done in the caller on the named local v -> v r37, idx r38, 100%. Dead ends: hand-expanding the inline merges the w->idx reload (98.4); an inline getter for idx merges the load too (98.1); swapping v/idx declaration order does nothing. Commit 106f96f37 on claude/g8d80-1029. Opposite direction to the BoxBodyModel getter lever, same colouring rule.
