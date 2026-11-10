# fn_8031FDC4: enum-typed ?: in call arg keeps arg setup before branch

- status: works
- tags: ternary,enum,branchless,arg-order,RPBow_8031EFE4,8031FDC4
- source: RPBow_8031EFE4 2026-10-29

symptom: original sets r3/r4 call args BEFORE a 'li r5,K1; beq; li r5,K2; bl' triangle; ours puts mr r3/li r4 in the join block (if-statement mode var), and an int ?: in the arg becomes branchless neg/or/srawi
cause: MWCC codegen folds int-typed c?K1:K2 into branchless code, but not enum-typed ones; a ?: left in arg position is evaluated in order after args 1-2, so their moves precede the branch. Comma/&&/inline-call args are hoisted out by IRO first
fix: fn_80320830(self, 3, flag != 0 ? BOW_ANM_4 : BOW_ANM_5) with a file-local enum BowAnmId -> 100%, unit DOL 0 on flip. Look for an enum type whenever a constant ?: shows a branch in the original
