# fn_802BBEB4 (RPGol_802bb608): name dz before the GolVec2 ctor to move the f2/f3 pair

- status: works
- tags: regalloc,fpr
- scope: RPGol_802bb608 fn_802BBEB4
- source: FPR batch 2 2026-10-28

symptom: 99.74: XZ distance f2/f3 swap (supersedes the 2026-10-13 open lesson)
cause: naming dz makes it an older vreg -> higher volatile f3; 0.0/len take f2 as target
fix: f32 dz = a->z - b->z; GolVec2 d(a->x - b->x, dz); 100%, no marker
