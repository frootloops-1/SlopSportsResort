# fn_802D98BC bytes-matched: inner BoxCond5z level + outer && in case body + k-first BoxScaleBy

- status: works
- tags: fn_802D98BC,RPBox_802cf93c,regalloc,mwcc_dbg,inline
- scope: RPBox_802cf93c

symptom: 5a result r27 vs target r23 (58 lines), then FPR f3/f2/f1 vs f2/f3/f1
cause: front-end @ temps (named, no CSE, coloured by descending vreg) come from inline-call && levels; a ?: or plain && at the deepest level gives a codegen temp (high vreg, coloured first, zeros CSE'd). Inline depth is 8, so a 9th level needs the outermost && moved into the case body. FPR: k must have the lowest vreg (created before the cvt temps) yet be the right operand of fmuls
fix: BoxCond5z(self)=w74==1?TRUE:FALSE as innermost; BoxCond5a = BoxCond5z(self) && BoxScaleBy(lbl_804BDC30,(u32)f84) > 80.0f with BoxScaleBy(k,v){return v*k;}; case 5: BoxCond5g(self) && (h1E & 1). 99.77 -> 100, R17 ledger 131
