# Early 'if (v<0) return' before switch reuses cr1 compare; Rect ctor FPR order -> two VEC2 locals; size-0x8 sdata2 pad

- status: works
- tags: switch,early-return,fpr,vec2,sdata2
- scope: Pack/RPKernel/RPSysHomeMenuMgr

symptom: checkMenuEnd 94.6; BanIcon::draw FPR order; .sdata2 95.65 identical bytes
cause: guard compare reused; Rect ctor arg evaluation order; last symbol includes 4 pad bytes
fix: early return guard before switch, drop NULL case; two VEC2 locals size then pos by field assignment; set last sdata2 symbol size to 0x4
