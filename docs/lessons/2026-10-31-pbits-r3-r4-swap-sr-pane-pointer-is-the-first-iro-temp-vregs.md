# pBits r3/r4 swap: SR pane pointer is the first IRO @temp (vregs reverse creation order above named locals); hold the base in a one-field struct so IRO scalarizes it to an early high vreg (R17)

- status: works
- tags: rpbow,80351830,80351444,iro,strength-reduction,vreg,scalarize,r17,fpr-declaration-order
- source: worker pbits 2026-10-31

symptom: 99.7/99.4%: bit-test loop base pointer r4 vs target r3 (addi r3,ctx,0xc20), plus f0/f1 (f1/f2) table-load swap, plus lbz 0xc34(r4) vs (r30)
cause: IRO_DoStrengthReduction creates the pane pointer as the first IRO temp; @temps take vregs in reverse creation order above all named locals so a named pBits is always coloured after it
fix: struct BowBitRef { const BowBitSet* p; }; BowBitRef ref = {&pCtx->mBits}; ref.p->Test(i): IRO_ScalarizeClassDataMembers makes ref.p an early @temp with a higher vreg, coloured first (ledger rows 37/38). FPR swap: declare the second-loaded local first (f32 py; f32 px = t[0]; py = t[1];). Param-reg propagation: bool reverse = a == 0 || b; instead of false+if-assign. Dead: inline accessor, const ref, const ptr, comma expr, loop-local pBits, inline helper holding the loop, const-ref temporary, BowPinStatus direct bits[] (96). Tool: mwcc_frontend_trace.py --frontend-limit 200 shows which IRO pass creates each @temp (~7 s).
