# fn_803395E4: BowSphRef holders fix sphJ/si GPRs; fabsf inline + inlined weights fix the FPR contact block

- status: works
- tags: RPBow_803381DC,fn_803395E4,holder,fpr,fabsf,regalloc
- scope: Pack/RPSports/RPBowScene

symptom: sphJ/si named locals coloured last (r20/r19) vs retail r29/r23; then FPR vi/vj/wi registers off in the contact block
cause: named pointer locals rank below IRO temps; __fabs directly gives different vreg ages than MSL fabsf's (float)fabs((double)x) inline; named wi/wj locals colour later than retail's expression temps
fix: BowSphRef{BowPinSphere* p} sphJ.p=pj->sph; sphI.p=pi->sph; si=&sphI.p[a] in the a loop (GPRs exact). Order rel,pen,vr,vi,vj; vi=fabsf(dot) with MSL-shaped local fabs/fabsf (including <cmath> regressed to 90.5); imp before weights; weights inlined into n*imp*(vj/(vi+vj)). 97.9 -> 100, unit flipped Matching. Harness path 113->57->34->27->18->0.
