# Swapped callee-saved GPRs between pointer locals: hold &ptr->member

- status: works
- tags: regalloc,r30,r31,pointer
- scope: RPGol_802c58d4
- source: claude/rpgolscene-unsplit

symptom: r30/r31 swapped between a vec pointer and a struct pointer
cause: allocation order follows the pointer variable kind
fix: float* pinPos = scene->pin->v54 instead of the struct pointer; MWCC folds the offset into displacements and the order flips
