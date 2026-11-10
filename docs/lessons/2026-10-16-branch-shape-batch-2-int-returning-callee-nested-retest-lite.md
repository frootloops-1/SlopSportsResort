# branch-shape batch 2: int-returning callee, nested retest, literal ternary, single-case switch dispatch

- status: works
- tags: branch,BRANCH-SHAPE,ternary,switch,dont_inline
- source: claude/nm-3 2026-10-16 sonnet worker 2

symptom: BRANCH-SHAPE near-misses (RPSports, WPADMem, RPGolConfig)
cause: decomp simplified conditions / wrong callee return types
fix: neg/or/srwi on a bool helper result = callee returns int; repeated sp&&sp->f8 test = nested if with the same test in else; BOOL ternary goes branchless only with literal constants (?0:-2); error-path callback outside the if; extra 'case 1: break;' gives cmpwi 1;beq;bge; s32 not u32 for xoris; bool x=false; if(w){if(c)x=true}else x=true keeps two li paths; stub inlined under -inline deferred: #pragma dont_inline blocks header inlines inside it too. Failed: __VIInit dead b;b, fn_801EB7A0 bool select, SIInterruptHandler unfolded shifts
