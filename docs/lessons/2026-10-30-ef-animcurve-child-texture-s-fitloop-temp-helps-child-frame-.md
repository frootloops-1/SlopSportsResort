# ef_animcurve Child: Texture's fitLoop temp helps Child frame helper (696->692), not shared CalcCurveFrame/CalcCurveFrameF

- status: works
- tags: ef_animcurve,Child,fitLoop

symptom: Child 696 diff lines; same int->float f0/f1 conversion symptom as Texture
cause: copy of u32 loop into the by-ref param shifts the pre-RA schedule so the loop*length lfd is live when the tick conversion is defined
fix: In CalcCurveFrameChild fitting branch: u32 fitLoop = ...; loop = fitLoop; use fitLoop*length. Applied to shared CalcCurveFrame and CalcCurveFrameF too: no change at all. Branch claude/ac-tex2-1029
