# ef_animcurve Texture: CalcCurveFrame written out in body + count before n

- status: works
- tags: ef_animcurve,regalloc,inline-boundary
- scope: nw4r/ef/ef_animcurve
- source: claude/ac-*-1028

symptom: frame/len lhz in r7 vs target r8; n=len-1 not sharing tick reg
cause: inline helper boundary gives frame value a different vreg age
fix: write CalcCurveFrame body in the function (not an inline); in TURN+FITTING declare u8 count before s32 n=length-1: 99.42->99.53. Left: pCmdList copy coloured last (r24) vs first (r31)
