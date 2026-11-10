# load+ori register swap: use s32 v = f; f = v | 1

- status: works
- tags: ori,register-swap
- scope: RPSportsCommon_unsplit

symptom: r4/r5 swap (97.5%) with self->f |= 1 after an unrelated store
cause: compound assign reloads/schedules differently
fix: s32 v = self->f6C; self->f18 = 0; self->f6C = v | 1;
