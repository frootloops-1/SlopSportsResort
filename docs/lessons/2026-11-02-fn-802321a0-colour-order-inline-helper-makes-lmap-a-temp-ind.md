# fn_802321A0 colour order: inline helper makes lmap a temp, index/lm locals

- status: works
- tags: regalloc,gpr,inline,RPTns
- scope: RPTns_802318a4

symptom: mm r29/lm r30 vs target mm r30/lm r29/index r31 (99.0)
cause: locals are numbered below temps; the target coloured lmap, off, mm (temps) before lm and index (locals); declaring all of mm/lm/lmap as locals gives 93.8 regardless of order
fix: keep int index, RPGrpModelManager* mm, EGG::LightManager* lm as locals and get lmap through a static inline TnsGetLmap(mm) temp. Side effect: fn_802321A0 is auto-inlined into fn_80232248 and recolours there, so fn_80232248 needs its own old-shape inline (MATCH-PENDING R17)
