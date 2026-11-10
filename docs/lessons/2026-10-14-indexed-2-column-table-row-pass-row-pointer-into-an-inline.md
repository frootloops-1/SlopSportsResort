# Indexed 2-column table row: pass row pointer into an inline

- status: works
- tags: table,lwzux,regalloc,inline
- scope: RPTns_802437cc
- source: opus worker 2026-10-14

symptom: extra saved base pointers, scrambled allocation (82%)
cause: orig reads e[0],e[1] from a row pointer (addi+lwzux+lwz 4)
fix: static inline f(t, msg, const u32* e){ t->setMessage(msg,e[0],e[1],0); } called with tbl[i]; fix pressure issues before re-trying decl orders (fn_80243A14)
