# ef_animcurve U8 closed: forecast key setup reads flags through value pointers

- status: works
- tags: ef_animcurve,U8,regalloc,forecast
- scope: nw4r/ef/ef_animcurve
- source: claude/fc-animcurve-a

symptom: U8 99.58/20 lines tail key setup (k0/k1/v1 colour, neg0 temp, add k1 order)
cause: forecast AnimCurveExecuteU8Vec3 shape: pKey=keys+idx*keySize; v0=pKey+12; k0=v0-12; v1=keys+(idx+1)*keySize+12; k1=v1-12; interp=pKey+4; r0=k0[2]!=0; r1=k1[2]!=0 (no flag locals) changes vreg identities
fix: U8 99.58403 -> 100, no marker. Needs the separate pKey name: same without pKey (v0 from keys, interp=k0+4) is 99.3.
