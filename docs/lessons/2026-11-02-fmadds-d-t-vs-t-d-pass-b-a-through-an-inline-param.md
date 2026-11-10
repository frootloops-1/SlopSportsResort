# fmadds d*t vs t*d: pass (b - a) through an inline param

- status: works
- tags: fmadds,operand-order,lerp,RPGol_802c58d4
- scope: Pack/RPSports/RPGolScene
- source: opus pass 4

symptom: lerp fmadds f4,f1,f0,f2 (t*d) vs target f0,f1 (d*t); named-d golLerpA fixes order but swaps regs
cause: direct (b-a)*t+a / a+(b-a)*t spellings canonicalise to t*d
fix: golMadd(x,y,z){return x*y+z;} golLerpC(a,b,t){return golMadd(b - a, t, a);} (MATCH-PENDING R17)
