# arr[4-i] in three branches: hoist s32 j = 4 - i

- status: works
- tags: mwcc,loop,index
- scope: RPGol_802bca94
- source: sonnet-worker

symptom: 86% subfic/add per branch differs
cause: CSE shape
fix: hoist s32 j = 4 - i; local
