# near_miss DATA-REF pool label can hide a real constant value difference (0.0 vs 1.0)

- status: works
- tags: F1,pool,value
- scope: ef_drawstripestrategy
- source: claude/nm-data

symptom: ef_drawstripestrategy GetInitialPrevAxis 99.95 flagged pool; target loads 1.0f, source had 0.0f
cause: wrong constant in source, same pool shape
fix: compare pool values of @N vs lbl_ before renaming; changed VEC3 to (1,1,1)
