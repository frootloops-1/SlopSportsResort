# Local f32 zero = 0.0f before a vector set keeps 20 in f0 and the pool order

- status: works
- tags: regalloc,sdata2,pool,vec3
- scope: mwcc
- source: RPTns_802390b0

symptom: VEC3(0,0,20-z): f0/f1 swapped or 0 pooled before 20
cause: literal pool order vs vreg order of the two constants
fix: f32 dz = 20.0f - p->z; f32 zero = 0.0f; v.set(zero, zero, dz);
