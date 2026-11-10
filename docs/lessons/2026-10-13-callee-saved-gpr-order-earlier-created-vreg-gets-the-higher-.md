# Callee-saved GPR order: earlier-created vreg gets the higher register

- status: works
- tags: regalloc,callee-saved,r31
- scope: RPGol_802c441c
- source: claude/rpgolscene-unsplit

symptom: two pointer locals in r27/r28 swapped
cause: params right-to-left then locals; first created gets the highest
fix: merge or reorder the creating expressions (one float* pin = ...->v54 instead of two pointers)
