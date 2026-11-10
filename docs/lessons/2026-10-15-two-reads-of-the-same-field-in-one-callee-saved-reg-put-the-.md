# Two reads of the same field in one callee-saved reg: put the second use in an inline taking the owner

- status: works
- tags: mwcc,regalloc,inline
- scope: RPTns_8023c74c
- source: claude/rptns-2

symptom: self->cur reloaded into r31 twice in orig; ours second copy r27
cause: local var after an inline gets a new priority
fix: static inline TnsKickAll(TnsMato* m, ...){ TnsMatoModel* g = m->cur; ... }
