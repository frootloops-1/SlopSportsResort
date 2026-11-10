# Const-first fmadds in lerp with inline-param range: float d = b - a; return a + d * t;

- status: works
- tags: float,fmadds
- scope: RPGol_802b1a0c
- source: fn_802B2F90

symptom: var-first fmadds
cause: lerp form
fix: GolLerpD: float d = b - a; return a + d * t;
