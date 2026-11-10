# 12-float transposed copy load order (RPGolMapObjBase)

- status: works
- tags: golf,float,transpose,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: sonnet

symptom: 98.5% with reverse-declared locals
cause: different alloc order than the 15-float copy
fix: declare t0..t11 ascending, assign t11 down to t0, then copy t0..t11 into m[] in index order
