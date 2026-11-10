# Store unrounded product, compare frsp copy: f32-returning sqrt inline

- status: works
- tags: float,frsp,sqrt,inline
- scope: RPTns_80219d24
- source: opus worker 2026-10-14

symptom: orig stfs f2 (unrounded) before fcmpo on frsp f1
cause: f32-returning FSqrt-style inline stored, compared via (f32)(f64)s
fix: static inline f32 SqrtF(x){return x<=0?0:x*FrSqrt(x);} f32 s=SqrtF(v); field=s; if((f32)(f64)s>1.0f)...
