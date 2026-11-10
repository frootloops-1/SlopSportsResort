# fn_801A2EFC: needs one extra loop-live temp per inlined copy leaving no code; do-while u8 gives exact regs +4 clrlwi

- status: fails
- tags: regalloc,winmgr,2EFC,do-while,temp
- scope: Pack/RPKernel/RPSysSystemWinMgr

symptom: 99.5 with split reset/start workaround (4 extra lwz) or 98.5 natural restart()
cause: original has extra temp per UpdateButtonAnm copy; 19 hypotheses nogain; plain static UpdateButtonAnm not inlined (49.7)
fix: unsolved; next: temps that vanish after allocation, permuter on register signature; diagnostic: split in only some copies and print per-copy register signature
