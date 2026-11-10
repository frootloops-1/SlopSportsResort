# ef_animcurve F32 remaining range palette needs seven coordinated identities in model

- status: open
- tags: ef_animcurve,F32,register-allocation,model,range
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: After mask r0 and corrected saved hierarchy, rangeSize remains r7 instead of r3; inline field values occupy r3-r5 first.
cause: Fresh f32-masks graph shows blockers 92,93,94,95,96,97,99. A late range identity fixes its small palette but delays table removal into wave3, breaking saved registers. Caller-only declaration swaps are flat.
fix: Models only: demoting seed values preserves saved roles but gives range r5; adding flag values gives range r6/loop r4. Seven coordinated identities around a hoisted range and loop can give range r3/loop r6/mask r0 while preserving saved roles, but keys/keySize/count/loFrame/nextLoop still differ. No small source transformation established; no broad seven-value rewrite compiled. Preserve actual f32-masks graph and avoid repeating standalone range references or declaration sweeps.
