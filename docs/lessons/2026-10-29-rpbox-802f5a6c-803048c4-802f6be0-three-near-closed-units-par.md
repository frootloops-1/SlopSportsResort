# RPBox_802f5a6c/803048c4/802f6be0: three near-closed units parked, all volatile/callee-saved colour swaps

- status: fails
- tags: RPBox_802f5a6c,RPBox_803048c4,RPBox_802f6be0,regalloc
- scope: RPBox

symptom: fn_802F65E8 99.6 (r10/r11 elem ptr, tbl copy temp r10 vs r0, level r0 vs r10); fn_80304B58 99.4 (body r22 vs r23, table ptr r23 vs r22, tail iterator r24/25 vs r23/24); fn_802F6E80 99.8 (mulhw chain r0/r4)
cause: 802F65E8: mwcc_dbg shows level vreg coloured before the 5 tbl copy temps so it takes r0; target has tbl[0] in r0 and level reusing elem's r10. 80304B58: strength-reduced table pointer temp (@354) gets a higher vreg than the named body local, so it is coloured first; target colours body first. 803048c4 .sdata 85.7% is only the 2-byte gap_ pad (alignment before next unit), not a source problem
fix: No gain: 802F65E8 tried level-before-tbl, inline tbl[elem->level], const tbl, kind reads, early continue, elem declared outside loop, 4 min generic regsearch (28 evals); 80304B58 tried body/j declaration moves, explicit names pointer local, generic regsearch (hoistbare:j scores better in regsearch but is 99.0 real); 802F6E80 already parked by earlier sessions. Experiments left uncommitted in /private/tmp/ogws-boxdata2-1028 (source restored)
