# ef_animcurve U8 plateau 90.2%

- status: open
- tags: ef_animcurve,regalloc
- source: decomp-hard U8 2026-10-22

symptom: _savegpr_17 vs _16; turn check beq vs bne/b
cause: compiler reuses key count instead of reloading lhz 0(pKeys)
fix: tried 1u trick, inline search, std::fabs, asm FAbs: all failed
