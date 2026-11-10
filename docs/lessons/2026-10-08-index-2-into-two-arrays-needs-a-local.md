# Index+2 into two arrays needs a local

- status: works
- tags: mwcc,index,offset-folding

symptom: mArr[chan+2] inline in two places scored 53.8%
cause: compiler folds +2 into constant displacements
fix: local s32 i = chan + 2 used for both indexes -> 100%
