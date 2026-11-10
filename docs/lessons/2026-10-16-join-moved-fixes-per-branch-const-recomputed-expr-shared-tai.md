# join-moved fixes: per-branch const, recomputed expr, shared tail, unrolled for, case source order

- status: works
- tags: join-moved,label,switch,branch,BRANCH-SHAPE,loop
- source: claude/nm-4 2026-10-16 sonnet batch 1

symptom: join-moved near-misses fn_801BF088, fn_80298C98, fn_801FBA98, fn_801FB91C
cause: decomp hoisted or merged per-branch code, mis-inverted conditions, used a loop-free ladder, or reordered switch cases
fix: fn_801BF088 89->99.4: dot=1.0f inside the dot<=-1 branch; w=0;if(2*(1+dot)<=0)w=0;else w=2*(1+dot)*FrSqrt(2*(1+dot)) (no CSE across call); out->w=0.5f*w before 1/w. fn_80298C98 94->99.9: inner if + always-call inside if(r==1); (!hidden||flag)&&x; shared scale tail out of the if; nw4r::math::VEC3Scale not PSVECScale; f32 out not Vec3. fn_801FBA98 85->98.9: li r5,i;cmpw r5,k ladder = unrolled for(i<4) over slots, load slot in each branch, u8 kk=fn(); s32 k=kk-1. fn_801FB91C 76->85: case blocks emit in source order (target case 2,0,1 -> write that order)
