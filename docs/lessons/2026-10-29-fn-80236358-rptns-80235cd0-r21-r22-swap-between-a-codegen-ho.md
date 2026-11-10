# fn_80236358 (RPTns_80235cd0): r21/r22 swap between a codegen-hoisted li 1 and an IR CSE shift temp is not a getter case; park

- status: fails
- tags: RPTns_80235cd0,regalloc,mwcc_dbg
- scope: RPTns

symptom: 99.82%, 12 diff lines: hoisted li 1 gets r22, idx<<2 gets r21 (h shares r21); target has const r21, idx*4 and h r22
cause: Both values have remaining degree <=28 in the simplify stack, so they pop in descending vreg order; the codegen-created constant (r95) outranks the IR CSE temp (r47). Flipping needs the constant below r47 or 2 more live GPR neighbours on the shift temp. Reading mwcc_dbg: a node is coloured in pass 1 in descending vreg order only if its remaining degree is <=~28, higher-degree nodes are coloured first, so check a vreg's degree before trying a getter or declaration-order lever.
fix: No gain: completed[idx]=1, named int one=1 (loop/function scope, copy-propagated), inline getter for idx (99.5), TnsSetDone store helper, done[idx] for the check (99.6), named int* slot (eliminated). Debug dumps in scratchpad w_t6358. Parked, no commit.
