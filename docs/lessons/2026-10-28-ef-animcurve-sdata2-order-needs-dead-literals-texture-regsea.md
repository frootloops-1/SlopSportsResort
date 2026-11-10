# ef_animcurve: .sdata2 order needs dead literals; Texture regsearch 4480 evals no gain

- status: works
- tags: ef_animcurve,sdata2,regsearch,marker
- scope: nw4r/ef/ef_animcurve
- source: session 2026-10-28

symptom: .sdata2 92.86: ours 0.0,1.19e-7,...,255,u32 magic,s32 magic,1.0; target 0.0,pad,u32 magic,s32 magic,1.0,1.19e-7,...
cause: retail creates 0.0, the two int->double magic constants and 1.0 before the rest; -inline deferred per unit does not change it
fix: dead statements 0.0f; 4503599627370496.0; 4503601774854144.0; 1.0f; at the top of AnimCurveExecuteU8 gives .sdata2 100 (marker, ledger row). Texture regsearch --generic 12 min, 4480 evals: best stays 61.2 (21 lines)
