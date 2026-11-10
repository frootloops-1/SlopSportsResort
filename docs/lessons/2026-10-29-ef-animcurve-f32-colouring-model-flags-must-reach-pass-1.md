# ef_animcurve F32 colouring model: flags must reach pass 1

- status: open
- tags: ef_animcurve,F32,regalloc,mwcc-debugger

symptom: F32 95.62: kindEnable r23/flags r27/tick r22 vs target r27/r22/r23; mask r5 vs r0
cause: mwcc_dbg + level sim (K=29, ascending scan, coalesced kept as neighbours) reproduces our order exactly. Target needs flags (CalcCurveFrameF local) in pass 1 while n/lo stays pass 2; flags has 31 neighbours, 29 at scan (needs 28). Rotate gets pass 1 because it lacks the kindEnable neighbour. Target mask r0 means mask coloured before GetRandomRangeStride @-vars
fix: Not found. Find which flags neighbour the original lacks (frame-calc code is identical, so it is a long-lived F32 var or pre-RA order). Sim script: scratch f32w/tools/sim.py <dump> 29
