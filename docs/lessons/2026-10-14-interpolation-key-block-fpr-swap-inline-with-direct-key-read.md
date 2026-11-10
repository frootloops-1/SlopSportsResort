# Interpolation key block FPR swap: inline with direct key reads, ratio declared first

- status: works
- tags: float,regalloc,inline,interp
- scope: RPTns_8022d590
- source: opus worker 2026-10-14

symptom: hi/lo/ratio FPRs swapped in 4x inlined key block (96%)
cause: lo/hi locals change load order
fix: static inline KeyCalc(Key* k, f32 t){ f32 r; f32 d = k->hi - k->lo; if(0.0f==d){...} else r=(t-k->lo)/d; ... } (RPTns_8022d590)
