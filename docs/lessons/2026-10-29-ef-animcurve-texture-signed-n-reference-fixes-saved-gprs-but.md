# ef_animcurve Texture signed n reference fixes saved GPRs but conditional lowering regresses

- status: fails
- tags: ef_animcurve,Texture,reference,register-allocation,conditional
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Fresh header phase plus const s32& n targeted tables/seed/tick/header/particle colours.
cause: Reference succeeds at saved-register map but ternary arm becomes memory expression and branch diamond. Scalar u8 endFrame restores branchless selection with different scalar register scheduling.
fix: Signed reference99.71850->98.02949/89 diff lines; u8 endFrame before ternary99.36997/14 lines. Both rejected by score gate. Saved-GPR map now target; two old FPR lines plus12 scalar scheduling lines remain. Preserve candidate evidence, get actual compiler dump before a new causal step.
