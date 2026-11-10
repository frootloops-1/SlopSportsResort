# ef_animcurve Texture closed: u32 loop temp copied into loop moves pre-RA schedule so conversion takes f1

- status: works
- tags: ef_animcurve,Texture,FPR,scheduling,copy
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Texture 99.97319: fitting non-turn branch tick conversion f0 vs target f1 (fsubs/fmuls), B before Y post-RA in both
cause: mwcc_dbg: FPRs coloured highest vreg first; conversion A only avoids f0 if the loop*length lfd Y is live at its def, i.e. pre-RA schedule puts Y before the fmuls. A coalescable int copy in the block (loop = temp) shifts pre-RA list-scheduler timing, then RA removes the copy so post-RA order is unchanged. Same symptom in Child first CalcCurveFrameChild instance (second instance has extra addi tick+1 and matches).
fix: u32 fitLoop = (u32)(tick*ratio/length); loop = fitLoop; frame = (s32)(tick*ratio - (f32)(fitLoop*length)): 99.97319 -> 100, no marker. Dead: named f32 for (f32)(loop*length) (12 lines, gets rescheduled after), ratio*tick operand swap (same 4), length*loop (6), s32 value then frame=value (same 4).
