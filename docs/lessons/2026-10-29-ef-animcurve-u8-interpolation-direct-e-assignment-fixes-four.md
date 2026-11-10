# ef_animcurve U8 interpolation direct e assignment fixes four FPR copies

- status: works
- tags: ef_animcurve,U8,FPR,coalescing,conditional
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Four U8Interp copies select e13/ft12 vs target e12/ft13, over100diff lines.
cause: Ternary phi e42 then copy to e58 coalesces to old42, reversing colour order. Direct assignments avoid old phi.
fix: Only U8Interp e ternary becomes f32 e; if bit clear e=0; else e=1.5. Leave s ternary and arithmetic identical. U8 99.18908->99.390755; normalized214->110lines, no other function regressions. No new helper/marker; branch semantics identical. Not full match.
