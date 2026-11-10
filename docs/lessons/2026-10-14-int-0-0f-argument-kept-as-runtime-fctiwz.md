# (int)0.0f argument kept as runtime fctiwz

- status: works
- tags: fctiwz,fold,float
- scope: RPTns_8024a5cc
- source: sonnet worker 2026-10-14

symptom: orig lfs+fctiwz of zero; MWCC folds (int)0.0f
cause: constant folding
fix: f32 z=0.0f; z += self->field*0.0f; (int)z (fn_8024AD18)
