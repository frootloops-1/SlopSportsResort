# ef_animcurve Child header casts at both frame calls leave phase regression unchanged

- status: fails
- tags: ef_animcurve,Child,header,coalescing
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Prior particle phase keeps old command for frame helpers and adds2mr.
cause: Changing both frame helper inputs to header casts canonicalizes to same particle-phase instructions, does not remove the coalescing problem.
fix: Both CalcCurveFrameChild calls consume reinterpret_cast<u8*>(pHeader):97.51491/704 lines, same rejected phase result vs97.88188 baseline. Reverted; actual graph needed before next Child lever.
