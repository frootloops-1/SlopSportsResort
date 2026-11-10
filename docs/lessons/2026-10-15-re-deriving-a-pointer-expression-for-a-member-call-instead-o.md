# Re-deriving a pointer expression for a member call instead of reusing the local fixes reg order

- status: works
- tags: permuter,regalloc
- scope: Pack/RPSports/RPGolScene

symptom: fn_80293978 99.85% register-only diff
cause: original recomputed (*(GolVObj**)((u8*)self->f70+4))->Find(..) rather than obj->Find
fix: call Find on the re-derived expression while keeping obj for the later entries[idx]
