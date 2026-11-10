# fn_80313F60: enum-typed local for an s32 field reload keeps it a named variable (closes const-vs-load r0 wall)

- status: works
- tags: regalloc,local-type,enum,copy-propagation,RPBow_80313028
- scope: Pack/RPSports/RPBowScene/RPBow_80313028
- source: claude/bow-80313028-1105

symptom: const 1 takes r4, reloaded s32 field takes r0; target the reverse; every int/long/u32/s8..u16/bool local merged into the load temp (copy-propagated)
cause: a local whose type matches/convertibly merges into the load temp is coloured like a temp (first); an enum-typed local from an s32 load stays a separate named variable, coloured after the const temp
fix: BowSceneMode mode = (BowSceneMode)arg->w8; if (mode == 0) ... (or an inline getter returning the enum). Field typed as enum + direct read or s32 local did NOT work. Sweep local types incl. an enum with fn_harness before anything else
