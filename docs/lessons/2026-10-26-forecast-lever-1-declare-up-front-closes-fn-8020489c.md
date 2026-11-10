# forecast lever 1 (declare up front) closes fn_8020489C

- status: works
- tags: forecast,regalloc,declare-order,RPSports_802041d0,fn_8020489C
- scope: fn_8020489C
- source: forecast-regalloc

symptom: fn_8020489C 99.99%: lwz 0x70 value kept in r29 instead of r31 across fn_801CE31C/fn_801CE040 in one branch; a sibling branch with its own block-local sel got r31
cause: the first branch reused the outer 'mode' variable (and a separate block-local was no better); the target used ONE named local shared by both branches
fix: declare 's32 sel;' uninitialised at function top and assign it in both branches (sel = *(s32*)(s+0x70); s32* pSel=&sel;): 100%, unit MATCH-CANDIDATE. Block-local and block-top uninitialised declarations gave no change
