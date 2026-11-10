# fn_8031FDC4 arg setup before branch: ternary/comma/inline-getter/if-else all fail

- status: fails
- tags: branch,args,scheduling
- scope: RPBow_8031EFE4

symptom: original hoists mr r3,self / li r4,3 above 'if(flag) mode=4' (li r5,5 / beq / li r5,4 / bl); ours emits them in the join block (92.9%)
cause: MWCC emits arg-reg copies at the call point in the join block; mwcc_dbg shows mode vreg r35 li 5 then bt then li 4, args only in B4
fix: tried: ternary (branchless neg/or/srawi), (mode=4):mode in arg, comma-void form, inline BowCamMode(flag) getter (all unchanged or worse 90.8), if/else two calls (83.0). Unsolved.
