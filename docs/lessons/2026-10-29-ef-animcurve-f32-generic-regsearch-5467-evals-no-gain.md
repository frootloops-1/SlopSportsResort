# ef_animcurve F32: generic regsearch 5467 evals no gain

- status: fails
- tags: ef_animcurve,F32,regsearch

symptom: F32 95.6%, rank 10, 388 lines, kindEnable r23 (target r27), flags r27 (target r22), life r22 (target r23), keySize range ends 285 vs 817
cause: colour order is vreg identity; generic hoists/type swaps/swaps cannot move it; opcode diffs are only schedule shifts
fix: generic regsearch -j4 12 min: best = baseline 1245.0 (op21 rank10). Do not repeat; needs a vreg-creation-time lever (rvalue ref, phase split) like U8/Rotate wins
