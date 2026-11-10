# Loop var that needs a callee-saved reg: fetch via inline getter + sub-inline for inner loop

- status: works
- tags: mwcc,regalloc,callee-saved,inline
- scope: RPTns_8023c74c
- source: claude/rptns-2

symptom: volatile regs exhausted in a no-call loop; orig gives node r29 and group ptr r11, ours group r31
cause: which vreg spills to callee-saved depends on vreg creation order through inlines
fix: TnsMatoReset(TnsGet(self,i)) with static inline TnsGet returning self->set->arr[i], and the per-group body as its own inline TnsGroupReset(g)
