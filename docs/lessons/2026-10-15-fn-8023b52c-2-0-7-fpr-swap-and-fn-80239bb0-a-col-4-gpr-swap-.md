# fn_8023B52C -2/0.7 FPR swap and fn_80239BB0 a<->col*4 GPR swap unresolved

- status: open
- tags: regalloc
- scope: mwcc
- source: RPTns_802390b0

symptom: B52C: lfs -2 -> f0 vs f1 (10 lines); 9BB0: brick a in r23 vs r25, col*4 temp r25 vs r23
cause: allocator ordering not reproduced
fix: tried: ~20 statement/expression forms for pos.z/hp, full 720-perm decl search (B52C); 40320-perm decl search, index forms, continue-loop, decl placement of a (9BB0)
