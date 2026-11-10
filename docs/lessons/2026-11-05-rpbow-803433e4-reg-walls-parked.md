# RPBow_803433E4 reg walls parked

- status: fails
- tags: RPBow,regalloc

symptom: fn_80344650 r26-r28 rotation; fn_80346440 li r0 vs r4
cause: scheduling/colour order
fix: regsearch generic 2384 evals no gain; obs decl in loop worse; count=unkC=8 and local n no gain
