# Dead local f32 forces an .sdata2 pool slot

- status: works
- tags: sdata2,pool,float
- source: RPTns_80216810

symptom: A float literal sits in the pool before its first visible user, so pool order is wrong
cause: MWCC pools literals at first declaration/use
fix: Declare a dead 'f32 eps = 0.001f; (void)eps;' in the earlier function; no code effect, reproduces the slot
