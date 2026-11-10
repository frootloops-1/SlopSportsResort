# ef_animcurve Texture: callee-saved rotation, whole-body inline reverses table order

- status: open
- tags: ef_animcurve,regalloc,inline-boundary
- scope: src/nw4r/ef/ef_animcurve.cpp

symptom: Texture 99.4: ours n>tables>seed>pParticle>pCmdList vs orig pCmdList>tables>seed>n>pParticle
cause: helper-internal n=length-1 takes top saved reg in ours; const/pHeader-only/AsHeader/CalcFrameStep variants leave order unchanged
fix: wrapping whole body in static inline reversed table order (94.0) - evidence inline boundaries drive numbering; parked
