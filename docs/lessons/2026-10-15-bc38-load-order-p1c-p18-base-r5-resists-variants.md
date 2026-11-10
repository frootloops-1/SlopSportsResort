# BC38 load order p1c/p18 (base r5) resists variants

- status: fails
- tags: regalloc,scheduling,dead-end
- scope: Pack/RPSports/RPTnsScene/RPTns_8022a740
- source: claude-opus

symptom: fn_8022BC38 99.4: orig lwz r5,0x14; lwz r3,0x1c(r5); lwz r30,0x18(r5); ours loads p18 first with base r3
cause: unknown; pre-RA order puts callee-saved load first
fix: failed: ~13 variants (locals both orders, uninit decls, inline with 2 ptr params both orders, TnsCams* param, member getters/methods, array param, a|b vs b|a). or. order fixed by inline returning b|a
