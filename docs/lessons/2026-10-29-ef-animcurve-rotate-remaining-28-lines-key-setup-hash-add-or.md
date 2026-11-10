# ef_animcurve Rotate remaining 28 lines: key setup, hash add order, sign temp are dead by reshaping

- status: fails
- tags: ef_animcurve,rotate,scheduling,dead-end
- scope: nw4r/ef/ef_animcurve AnimCurveExecuteRotate

symptom: Rotate 28 lines: tail key setup (k1 r11 vs r7, neg temp r7 vs r3, v0 sunk by pre-RA scheduler), dual hash add SH+L vs L+SH (both hashes), sign tmp lbz r0 vs r5
cause: mwcc_dbg: pre-RA list scheduler emits neg(r0) before add k1 and sinks v0; target needs add k1 < neg0 < or0 < lbz flag1. Hash operand order tied to const C3/C4 colouring.
fix: dead: 260-sample sweep of 9 key-setup decl orders (best = baseline; k1-before-r0 orders +6..+16 lines), t placement x top-14 orders (no gain), drop flag0/flag1 locals (352), GetRandomRangeStride for ra only (364), 15 hash expression shapes in a Rotate-local copy (best = baseline 28; L-first fixes add but swaps C3/C4 regs, 50-56), precomputed base=S+H (no change), neg0/neg1/random0/ra decl order (28/102).
