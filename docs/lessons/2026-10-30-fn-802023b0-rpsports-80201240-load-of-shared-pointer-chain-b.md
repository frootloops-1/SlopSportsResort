# fn_802023B0 (RPSports_80201240): load of shared pointer chain before struct copy fixes register layout

- status: works
- tags: struct-copy,schedule,rpsports
- scope: RPSports_80201240

symptom: 93.6%: tbl struct-copy lwzu/word regs and pointer reg differ (r3 vs r24)
cause: stw of word1 scheduled after msg load when msg is read after the copy
fix: read msg = *(lbl_804BF730+0x60) before tbl = *(SpMsgTbl*)... copy: 93.6 -> 99.5; remaining r30/r31 swap
