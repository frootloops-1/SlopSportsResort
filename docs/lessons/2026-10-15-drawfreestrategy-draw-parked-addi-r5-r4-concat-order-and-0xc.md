# DrawFreeStrategy::Draw parked: addi r5/r4 concat order and 0xc8 manager reload after GetSizeY switch

- status: fails
- tags: nw4r,ef,drawfree,park
- scope: nw4r/ef

symptom: 99.66%, 11 lines; orig reloads mParticleManager after Draw_GetSizeY switch and orders addi r5 before r4
cause: unknown, function-wide; same inline matches in line/billboard strategies
fix: tried: permuter 8min, epsilon via numeric_limits, direct PSMTXConcat, moving static helpers above Draw: none helped. asm_diff '-' lines are the original
