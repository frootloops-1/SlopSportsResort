# Float local order and single-load scale

- status: works
- tags: mwcc,float,regalloc

symptom: f0/f1 swapped after struct copy; 3 lfs instead of 1
cause: local declaration order drives FPR assignment; repeated member reads reload
fix: declare y local before x; load member once into local f32
