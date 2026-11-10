# Branchless index select

- status: works
- tags: mwcc,branchless

symptom: if (mode != 2) n = 0 emits a branch
cause: statement form
fix: s32 idx = mode == 2 ? n : 0 emits subi/subfic/nor/srawi/and
