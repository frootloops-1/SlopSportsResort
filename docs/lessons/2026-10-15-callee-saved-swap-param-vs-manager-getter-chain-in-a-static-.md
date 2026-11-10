# Callee-saved swap param vs manager: getter chain in a static inline taking the manager

- status: works
- tags: regalloc,callee-saved,inline,static-inline
- scope: RPSports_80208744
- source: claude nearmiss 2026-10-15

symptom: fn_80208BF0 99.2: orig p/data share r31 and mgr r30; ours mgr r31; decl order/split decl/local copies did nothing
cause: vreg creation order of the getPlayer(0)->p10 chain
fix: static inline RPSportsPlayerData* spGetData(RPSysPlayerMgr* m){return ((SpPlayerLink*)&m->getPlayer(0))->p10;} then data = spGetData(mgr) -> exact
