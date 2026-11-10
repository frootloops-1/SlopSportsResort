# label-only diffs: code wrongly nested in last case/if; beq+b = one-case switch

- status: works
- tags: branch,label,switch,if-scope,BRANCH-DEST,BRANCH-SHAPE
- source: claude/nm-3 2026-10-16

symptom: asm_diff shows only <label> lines moved (target label earlier), or target 'beq Lx; b Lend; Lx:' vs ours 'bne Lend'
cause: Hand/AI decomp put statements shared by every path inside the last switch case or inside an if; or wrote if(x==K) for switch(x){case K:}
fix: Move the statements after the switch/if so all paths reach them (target label position shows where the join is); 'beq; b; label' = switch with one case. Fixed fn_8020582C, fn_801EE18C (new-obj store after if(p)), fn_80201A48, fn_801EBA74. Scan: asm_diff over near-misses, keep ones whose diff lines include <label>
