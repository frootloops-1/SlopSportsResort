# fn_802FBBE4 (RPBox_802f9f50): ternary-of-constants join value keeps f2 under every spelling

- status: fails
- tags: regalloc,fpr
- scope: RPBox_802f9f50 fn_802FBBE4
- source: FPR batch 2 2026-10-28

symptom: 99.57, opcodes identical; ternary 0.08f:0.3f in f2 (target f1), f00 load f1 (target f2)
cause: pure colouring wall; operand swap canonicalised, named k / spin no effect, inline returning the ternary no effect, hoisting the f00 load changes scheduling (86.4)
fix: none; park
