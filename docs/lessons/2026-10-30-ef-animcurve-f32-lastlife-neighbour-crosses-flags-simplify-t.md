# ef_animcurve F32 lastLife neighbour crosses flags simplify threshold

- status: works
- tags: ef_animcurve,F32,register-allocation,simplify,reference
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Inline flags and n each have 29 neighbours at their first scan. Flags takes r27, displacing kindEnable to r23.
cause: Visit n before flags, then give the existing life-1 value an earlier named identity with two uses. This removes a neighbour before flags is scanned. The actual graph confirms flags enters wave 1 while n stays in wave 2.
fix: Use an R17-marked F32-only CalcCurveFrameFLocal clone; hoist n before frame, declare lastLife before flags, assign it at the existing tick>=life-1 comparison, and use it in only the final scale denominator. Hoist the caller kindEnable declaration while preserving its load site. F32 95.615616 -> 95.85085; 772 -> 724 changed lines, identical opcode counts, other five functions unchanged, .sdata2 100%. Frame helper/prologue matches through instruction 218. Applying the edit to the shared helper regresses Rotate 99.1673 -> 99.11531, so retain the local clone. Not a full match.
