# ef_animcurve shape idioms

- status: works
- tags: ef_animcurve,turn,interp
- source: decomp-hard F32 2026-10-22

symptom: bne/b turn check, interp ternary polarity, late clrlwi
cause: inline shape differences
fix: TurnFrame early-return inline; interp const 1.5 with !((t>>2)&1)?0:1.5; frame inline returns s32, cast u16 after mask loop; volatile u16* key count reload; separate idx var
