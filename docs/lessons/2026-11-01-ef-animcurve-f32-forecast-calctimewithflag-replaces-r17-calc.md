# ef_animcurve F32: forecast CalcTimeWithFlag replaces R17 CalcCurveFrameFLocal at equal score; full F32N port and SearchKeyStride helper regress

- status: open
- tags: ef_animcurve,F32,forecast,regalloc
- scope: nw4r/ef/ef_animcurve
- source: fc-animcurve-b 2026-11-01

symptom: F32 95.95/610 lines, frame calc needed an R17 clone; remaining diff is volatile-reg colouring from the bit-scan onward (orig count r10, ours r9)
cause: Frame part is forecast CalcTimeWithFlag(pHeader,flag,frameLength,tick,life,u16&,u32&,f32&)+CalcFittingTime with frameLength<=1 split in caller; key/search part still not the retail shape
fix: Keep CalcTimeWithFlag (identical 95.95095, R17 clone gone). Full forecast F32N port (ByteTable* tables, key struct, ScaleRnd, SYNC-gated MixRandom): 92.2, callee-saved order shuffled. Forecast SearchKeyStride (int keySize, u16 prev/next) in old body: 95.9/645 lines. Both reverted
