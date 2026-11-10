# Constant-count fill loops in ctors: opt_unroll_loops off + do-while countdown

- status: works
- tags: loops,unroll,ctor
- scope: RPTns_8022e3f8

symptom: ctor ring-buffer fill and 6-float clear unrolled or wrong loop shape
cause: MWCC unrolls constant-count loops
fix: #pragma opt_unroll_loops off around the ctor; ring fill as do-while over Vec2* with end pointer declared before start; float clear as s32 n=5; do { hist[n]=0.0f; } while(--n>=0) (for-loop and pointer walk fail)
