# Aggregate init {1.0f, x} with a literal pools an 8-byte struct template in .sdata2

- status: works
- tags: sdata2,pool,aggregate
- scope: Pack/RPUtility/RPUtl_801C67B8
- source: claude/rputl-c67b8-1027

symptom: extra 8-byte @N objects (1.0, 0) at the head of .sdata2 and lwz/lwz copies instead of stfs of a register
cause: MWCC pools a partially constant aggregate initialiser at parse time
fix: write field assignments (p.x = 1.0f; p.y = ...) instead of = {1.0f, ...}; VEC2 ctor grows the frame
