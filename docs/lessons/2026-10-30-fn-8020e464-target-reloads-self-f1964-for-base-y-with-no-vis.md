# fn_8020E464: target reloads self->f1964 for base.y with no visible killer; 12 spellings all CSE'd

- status: open
- tags: fn_8020E464,RPSports_8020b294,reload,cse,alias
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b294

symptom: target has a second lfs 0x1964(r30) feeding stfs base.y (0x14) after the h fsubs; ours merges it (initial pcode has both loads, backend optimizer removes the second)
cause: unknown: the backend CSE only kept the reload when base was an escaped aggregate (struct {b,a,CurPos base} with &q.a,&q.b passed), but then the scheduler keeps stfs 0x10/0x14 before the r30 loads, unlike the target
fix: failed: h before base.x, base.y before base.x, CurPos* pb stores, *&self->f1964, (&self->f1960)[1], ((CurPos*)&self->f1960)->y, CurPos init list, struct copy (lwz/stw), SelBottom/SelHeight inline getters, SelSetPos(&base,..) inline, named bot local, assignment-in-expression. Untried: block boundary between the loads, a non-inlined-looking helper.
