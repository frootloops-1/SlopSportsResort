# Loop body as static inline taking the element pointer fixes GPR/FPR order

- status: works
- tags: regalloc,inline,loop,constants
- scope: Pack/RPSports/RPTnsScene/RPTns_8022a740
- source: claude-opus

symptom: AD90 98.6: elem in r5 not r3, hoisted -1.0f in f3 not f8
cause: inline param temps and constant-folded args get later vregs
fix: static inline Init(TnsAv* a, Vec3& p, Basis& b, f32 x, f32 z, f32 sx) called with arr[idx[i]]; outer p/b passed by ref keeps one stack copy; store b.z row (-sx) before b.x row, after p
