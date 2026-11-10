# fn_802A8850 CSE temp vs strength-reduced cursor colour swap: hold the expression in an inline local

- status: works
- tags: regalloc,inline,cse,vreg-numbering,RPGol
- source: RPGol_802a7a40 2026-11-04 opus

symptom: loop cursor r27 / run length (i - runStart) r26, target reversed
cause: i-runStart used in compare and as call arg became an optimizer CSE temp created after the strength-reduced cursor (newer @ id -> lower vreg -> coloured later). Inline params/locals are created at expansion, before the IR optimizer, so they number above the cursor; named fn locals number below all @ vars
fix: static inline GolTry(start,end,int& best,int& bestLen){int len=end-start; if(len>bestLen) best=GolPick(start,end,len,bestLen);} at both call sites; 99.7->100. mwcc_dbg names vregs (@NNNN ids show creation order)
