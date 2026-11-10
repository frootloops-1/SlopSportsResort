# fn_801BB9B8 inline corner helper param copies swap c/x FPR colours; write blocks out

- status: works
- tags: fpr,regalloc,inline-helper,RPUtlCollisionModel
- scope: Pack/RPUtility/RPUtlCollisionModel
- source: claude/rputl-cmod-1027

symptom: corner blocks: cosine and quotient x get f8/f7 swapped vs target
cause: inline helper parameter copies change the vreg order of the cosine vs the in-helper temps
fix: write the three corner computations in place (no static inline helper): 144 -> 128 lines
