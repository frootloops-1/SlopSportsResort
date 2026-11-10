# fn_80280DF4 (RPBsb_802803b0): declaring p before c fixes sum/half exactly but prod takes sum's f1

- status: fails
- tags: regalloc,fpr
- scope: RPBsb_802803b0 fn_80280DF4
- source: FPR batch 2 2026-10-28

symptom: 99.07; order s,p,t,c gives sum=f1 half=f0 (target) but prod f1, c f6 (target f2/f3): 98.6
cause: vreg creation order of p's int-to-float temps matters (confirms model) but a second node then shares sum's register
fix: none: orders t,p,c / p,c,t / t,c,p (98.6/97.9/identical), no named sum, BsbTriSum inline (flat/97.2), split prod (97.9), clamp in initialisers (21.3). partial lead only
