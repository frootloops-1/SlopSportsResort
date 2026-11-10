# fn_80303DB4 FPR colouring wall: write vector lerps per component through a scalar inline LerpF so member loads/results become IRO temps with low vregs (R17 ctor + helpers + one, ledger 41-43)

- status: works
- tags: rpbox,80303db4,fpr,lerp,iro-temp,by-value,r17
- source: worker vreg-3db 2026-10-31

symptom: 96.9%: stack slots/store order differ and unk74 x/z results f30/f31, unk68.x f29 coloured wrong; ~20 diff lines in head lerps and the u/v2 LerpR block
cause: vector-wide lerp helpers taking const& (LerpR/LerpV/member Lerp) leave loads as back-end temps (high vreg, coloured first); a scalar inline with scalar params turns loads/results into IRO temps with low vregs, coloured late
fix: static inline f32 LerpF(a,b,t){return a*(1-t)+b*t;} per component x,y,z (x,z,y 99.9) for unk74, unk68 and unk5C (keep f32 one local; literal 1.0f 94.9); w2 as a two-Ratio ctor without named r3 (f32 r3 = Ratio(..) makes 1-r3 a back-end temp, 92.8); stack: invented BoxVec3(BoxVec3 v,int) by-value ctor, first declared before second. Dead: by-value LerpR params 92.8-92.9, operator form 90.7, by-value return 80.9, by-value helper 98.8, by-value POD ctor 93.0, regsearch --generic (5 sites, 130 evals). Removing all 4 unused lerp helpers renumbers @N literals (SIZE-MISMATCH) so they stay: re-run unit_cmp after dead-code cleanup.
