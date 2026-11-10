# RPBox_802f9f50: local static table, ternary base, BoxItemScale accessor; fn_802FC584 dead ends

- status: works
- tags: local-static,alias,fn_802FAE40,fn_802FBBE4,fn_802FC584,RPBox
- scope: Pack/RPSports/RPBoxScene/RPBox_802f9f50
- source: unit sweep 2026-11-01

symptom: fn_802FAE40 98.9 unrolled table load blocked by stores; fn_802FBBE4 99.6 ternary join f2 vs f1 (recorded wall); fn_802FC584 98.5 register residue
cause: file-level table stays tied to stores through self; accessor result IRO temp numbering sets FPR colour; e/child folded into operator-new temps
fix: FAE40: function-local static table + arg order + ternary base (symbol becomes lbl_804BE928$905, rename in symbols.txt before flipping); FBBE4: static inline BoxItemScale(BoxItem*) (R17 row 49), inner-BoxObj18* helpers 86.4; FC584 dead: decl order, in-loop decls, void* casts, assign-in-if, ctor forms, state init helper, 10-min regsearch; @stringBase0 264!=259 is 5 trailing zero pad bytes
