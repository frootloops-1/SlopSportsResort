# Scalar inline helper per component fixes lerp regalloc; arg order flips load order (RPGolUtlVec fn_80295E44)

- status: works
- tags: rpgolutlvec,inline-helper,load-order,float
- scope: RPGolUtlVec
- source: opus

symptom: plain expression 84%, locals 66%, fneg forms worse
cause: MWCC reschedules inline helper args; named locals not reordered
fix: static inline f32 CubicEase(a,b,t)=a+(a-b)*t*t*(2t-3) called per component as (a->x,b->x,t) -> 100%
