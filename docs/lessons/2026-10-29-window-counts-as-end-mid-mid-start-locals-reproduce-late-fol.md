# Window counts as end - mid / mid - start locals reproduce late-folded loop counts naturally

- status: works
- tags: unroll,loop,mwcc,iro,802c8360,rpbox,marker-removal
- scope: mwcc
- source: claude/q-boxrename-1029

symptom: fn_802C8360 needed the counts 80 and 6 opaque at IRO unroll time (variable-count x8 unroll, remainder-only 6-loop, runtime u32->f32 divisors); previous spelling nAll=86; nS=nAll-80; nL=nAll-nS was a MATCH-PENDING marker
cause: any binary op on propagated locals folds only after unrolling; a plain copy (nS = mid) folds before it (92.2%)
fix: u32 start = 0, mid = 6, end = 86; nL = end - mid; nS = mid - start; pass mid/start as the window starts: 100%, no marker needed. Look for natural bound-subtraction (length = end - begin) before inventing arithmetic
