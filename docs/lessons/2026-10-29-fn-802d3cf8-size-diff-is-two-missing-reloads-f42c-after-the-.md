# fn_802D3CF8: size diff is two missing reloads (f42C after the v450 stores, w680 after the w4D8 store)

- status: open
- tags: fn_802D3CF8,RPBox_802cf93c,size-mismatch,alias,cse
- scope: RPBox_802cf93c
- source: claude/box802cf-r2-1029 opus

symptom: 2916 vs 2904: target reloads self->f42C for BoxClamp after v450.x/y/z = f42C/f430/f434 and reloads w680 inside if (w680 & 4) { w4D8 = 7; w680 &= ~4; }
cause: retail has an alias kill (store through a pointer/other type, or an out-of-line-looking access) that our member stores lack, so IR CSE reuses the loads
fix: failed: BoxV3Pod* pv = &self->v450 member stores (folded, 145 lines). Untried: v450 set through a non-inlined-looking helper, w680 accessed through a BoxObj* view
