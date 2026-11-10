# 3-float copy with x kept live: declare z first, assign x,y,z

- status: works
- tags: float,regalloc,struct-copy
- scope: RPTns_802318a4
- source: claude/rptns-2

symptom: lfs f3,f1,f0 load x,y,z then 3 stfs, x kept for later multiply; *out=*in interleaves, plain locals give y->f0 z->f1
cause: 2nd defined float local gets f0, 3rd f1
fix: f32 z; f32 x = in->x; f32 y = in->y; z = in->z; out->x=x; out->y=y; out->z=z;
