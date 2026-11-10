# fn_8032212C: callee-saved FPR one too high -> direct cos() + hoist later block locals

- status: works
- tags: RPBow_80320EFC,regalloc,fpr,callee-saved,inline-return-temp
- scope: fn_8032212C

symptom: cos result f30 vs retail f29, f30 unused in that block
cause: callee-saved pick = lowest free among already-handed-out regs; c (BowCos inline return @temp) coloured before b11 speed/y, retail colours it after them
fix: f32 c = cos(r); f32 s = sin(r) (no inline wrapper, assignment truncates) + declare speed,y uninit at function top: harness 25 -> 22
