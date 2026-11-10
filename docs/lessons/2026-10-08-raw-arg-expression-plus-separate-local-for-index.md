# Raw arg expression plus separate local for index

- status: works
- tags: mwcc,regalloc

symptom: extra mr r28,r4 / mr r0,r31 in original not reproduced (96.1%)
cause: original used (chan+2) expression for a field and a local for array indexing
fix: SetDataSource((RFLDataSource)(chan+2)) from raw chan plus local s32 i = chan+2 for arrays
