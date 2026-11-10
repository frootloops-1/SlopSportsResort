# ef_animcurve Child closed by forecast CalcFrameStep (f32 return, u16& frame out) + C89 shared loop vars

- status: works
- tags: ef_animcurve,Child,forecast,int-to-float
- scope: nw4r/ef/ef_animcurve
- source: fc-animcurve-b 2026-11-01

symptom: Child 97.89 parked: int->float stack-slot alternation in 2nd inlined frame copy + register permutation (692 lines)
cause: Retail helper is forecast's CalcFrameStep(u8*,tick,life,u16& rFrame,u32& rLoop,bool& rEnd) that zeroes rLoop/rEnd itself and returns f32 rFrame (unused): the dead u16->f32 return conversion makes conversions per copy even, fixing slot alternation; earlier single-shape trials changed only one piece at a time
fix: Port forecast AnimCurveExecuteChild verbatim (header+1 table casts, top-level C89 frame0/loop0/end/end1/frame1/loop1/i/pKey/loop, middle loop tests loop0&1 not a cached backward) with CalcFrameStep and SearchKeyStep naming firstFrame: 97.89335 -> 100, no marker
