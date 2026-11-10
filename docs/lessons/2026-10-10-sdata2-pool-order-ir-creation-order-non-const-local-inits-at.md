# sdata2 pool order = IR creation order; non-const local inits at declaration, literals at first use (fn_802966B4 order 70,64,191,30 vs 70,30,64,191)

- status: open
- tags: rpgolmapobjtree,sdata2,pool-order,regalloc
- scope: RPGolMapObjTree
- source: opus

symptom: exact constant order via non-const locals drops code to ~94%
cause: locals kept in regs, loaded up front
fix: unresolved; parked
