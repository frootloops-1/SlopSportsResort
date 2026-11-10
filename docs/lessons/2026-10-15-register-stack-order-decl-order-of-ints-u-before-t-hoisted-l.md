# Register/stack order: decl order of ints, u-before-t, hoisted loop vars

- status: works
- tags: regalloc,stack,declaration-order
- scope: mwcc
- source: RPTns_802390b0

symptom: address-taken ints/vec temps in reversed stack slots; FPR t/u swapped; loop row/col regs swapped
cause: MWCC stack slots descend in textual declaration order (nested-scope decls after); shared loop vars follow decl order
fix: declare in target slot order (c0,r1,c1,r0); f32 u = 1.0f - hp; f32 t = hp; hoist int col,row,any to fn top; permutation search with a 0.3s compile harness
