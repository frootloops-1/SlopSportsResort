# Loop limit field typed s32 (= long in types.h) vs int counter blocks (n+3)-1 -> n+2 fold in unroll overflow pre-check; retype to int

- status: works
- tags: unroll,loop,s32,long,int,fold,rpbow,8034c230
- source: worker nx-f230 2026-10-31

symptom: 99.1%: unrolled sum loop preheader computes n+3 once then subi r0,r9,1 where the target reloads and computes n+3 and n+2 separately; 13 loop-bound spellings flat/worse
cause: include/types.h s32 is signed long; field_20 + 3 is long compared against int i, the conversion node blocks MWCC folding (n+3)-1
fix: declare the limit field int (local BowSceneState::field_20 s32 -> int): 100%. When a sibling loop with a plain int count folds limit-1 and the target does not, check s32-vs-int mixing before reshaping the loop.
