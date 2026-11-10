# fn_8031A0E0 wall 2 closed: model phase-0 sched + colouring, then height-first order + dist copy

- status: works
- tags: A0E0,RPBow,rate,fpr,schedule,regalloc,model
- scope: fn_8031A0E0
- source: round 11

symptom: 4 rate lerps: retail rate f6 and temp colours unreachable by any statement/operand order
cause: Colour model (phase-0 sim order -> live ranges -> lowest-free colouring in descending vreg order) reproduced ours exactly and proved no list order of the traced graph reaches retail; adding a phase-0 fmr after the dist (and angle/height) fmadds raises its height so sd issues before the next load
fix: height lerp first, then f32 baseDist = lerp; dist = baseDist; (named copy -> fmr in phase 0, coalesced later), angle, fovy plain. Block exact, 98.5 -> 99.0 (R17 ledger 398). Scripts: /private/tmp/scratch-A0E0-r11/rcol.py rsearch4.py (sim + colour search incl. extra copy nodes), w12.py (compile sweep)
