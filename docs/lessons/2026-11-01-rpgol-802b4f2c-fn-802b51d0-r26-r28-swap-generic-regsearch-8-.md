# RPGol_802b4f2c fn_802B51D0: r26/r28 swap, generic regsearch 8 min no gain

- status: fails
- tags: regsearch,RPGol_802b4f2c,fn_802B51D0,register-swap

symptom: 99.8%, only r26/r28 callee-saved swap; regroles shows identical live-range features
cause: coloring tie-break between equal-cost vregs
fix: none: regsearch --generic -j3 8 min stayed at baseline (score 18, rank 4). Do not repeat; needs a vreg-creation-order lever
