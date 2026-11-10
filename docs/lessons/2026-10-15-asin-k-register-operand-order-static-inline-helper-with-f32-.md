# asin*K register/operand order: static inline helper with f32 temp

- status: works
- tags: float,asin,fmuls,inline,regalloc
- scope: Pack/RPSports/RPTnsScene/RPTns_8022a740
- source: claude-opus

symptom: yaw computed in f30 after compare instead of f29 before it; fmuls operands swapped
cause: inline expression scheduled differently
fix: static inline f32 AsinDeg(f32 x){ f32 a = asin(x); return a * K; } used for yaw and -AsinDeg(dot)
