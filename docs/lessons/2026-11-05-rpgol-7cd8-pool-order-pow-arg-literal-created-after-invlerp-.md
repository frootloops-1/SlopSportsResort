# RPGol 7CD8 pool order: pow() arg literal created after InvLerp divisor; bind-to-local fixes pool but breaks schedule

- status: works
- tags: pool,sdata2,constants,inline,RPGol
- source: RPGol_802a7a40 2026-11-05 opus

symptom: objdiff 100% but flip_gate 23 bytes: .sdata2 pairs (0.05,0.2) and (0.001,0.3) swapped
cause: pool constants are created in IR-generation order with inline expansion: an inline call in a call arg (GolInvLerp) is expanded before the outer call's literal arg is materialised; the target has the literal first but loads it after the divisor
fix: SOLVED 2026-11-05: plain division with a zero local, fn(0.05f, (d - zero) / 0.2f), see lesson inline-call-as-an-argument-pools. Failed: const local, wrapper inline binding the literal as param (GolSmooth, GolPowInv), range-form invlerp, literal arg inline in the call, (d-0.0f)/0.3f (fsubs folds). float local works for pool but moves the load first. Next: stripped placeholder fn with 7CD8's literal sequence (R17)
