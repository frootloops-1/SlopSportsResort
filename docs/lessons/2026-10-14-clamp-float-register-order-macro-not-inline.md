# Clamp float register order: macro not inline

- status: works
- tags: clamp,float,regalloc,macro
- scope: RPTns_8023e934
- source: sonnet worker 2026-10-14

symptom: const in f1, value in f2 swapped with inline clamp or hi/lo temps
cause: macro expansion loads the constant first
fix: #define CLAMP using (x) > (K)+(c) / (x) < (c)-(K) (RPTns_8023e934 fn_8023EA2C)
