# fn_801CA3DC set(pane) load scheduling wall (lfs after all MTX lwz)

- status: open
- tags: mwcc,scheduling,mtx-copy,wall
- source: RPUtl_801C9E7C

symptom: 8 set(pane) inlines: lfs size + lfs from stack MTX copy scheduled after the 8 unused MTX word loads; origin byte r10 vs r6; target also CSEs pane+0x88 across strcpy (mr r11,r27)
cause: unknown; IR order of size loads vs MTX copy (struct locals move loads early but add stack slots)
fix: failed: local read order (no effect), store order perms, helper with by-value args, Scale/Pair/VEC2 local (frame +0x40), const locals, const PaneView* (more CSE, worse), free inline helper, by-value getter, const-ref getter, VEC2 temps
