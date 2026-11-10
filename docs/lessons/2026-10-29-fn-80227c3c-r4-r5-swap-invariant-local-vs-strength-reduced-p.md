# fn_80227C3C r4/r5 swap: invariant local vs strength-reduced pointer

- status: works
- tags: regalloc,r4-r5,inline-getter,RPTns_80227918

symptom: loop-invariant local (int lim=cfg->fc) got r5 and optimizer's strength-reduced pointer r4, target opposite
cause: named locals numbered reverse-declaration; optimizer pointer vreg (r54) numbered above all named locals and is coloured first (takes r4). Target needs lim coloured first
fix: static inline int TnsCfgFc(TnsCfg* c){return c->fc;} and int lim = TnsCfgFc(cfg); (fresh higher-numbered vreg) -> 100%. Failed: decl reorder, inline cfg->fc in loop (not hoisted), for loop, top-of-function decls, const, compare swaps. Found with tools/mwcc_dbg.sh (8s)
