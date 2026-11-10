# spCurrent in r31: static inline GetCurrent() as CreateData this

- status: works
- tags: regalloc,callee-saved,getter
- scope: Pack/RPSports/RPTnsScene/RPTns_8022a740
- source: claude-opus

symptom: spCurrent load in r29 instead of r31 (shared with handle)
cause: named local / member call order
fix: RPGrpModelResManager::GetCurrent()->CreateData((Type)12, fn_801BD648(...), 0) with a local class decl
