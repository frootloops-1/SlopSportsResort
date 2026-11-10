# fn_8032212C: front-end address CSE of &d->tbl[i] makes shift temp colour first; distinct base on one term fixes

- status: works
- tags: regalloc,cse,lerp,RPBow_80320EFC,fn_8032212C,fn_80320EFC
- scope: Pack/RPSports/RPBowScene/RPBow_80320EFC

symptom: lerp index i<<2 and data pointer d swapped GPRs (ours shift r3, i/d r5; retail lbl/d r3, i r4) despite every decl/type/expr-order spelling
cause: backend-00 shows the front end CSEs the whole address &d->tbl[i] into temps (S, d+S) numbered after the lbl load, so they colour first; descending vreg order
fix: spell one tbl[i] term via lbl_804BF9A8->data->tbl[i] (distinct base): only i<<2 is CSE-d as a low var -> fn_8032212C 99.8->100, fn_80320EFC 99.3->99.6 (R17 271). Dead: int byte offsets, i<<=2, shift locals, no-d forms, member/param helpers; (d=lbl->data)-> in-expression is UB and miscompiles
