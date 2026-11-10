# extern const GolShCol changes scheduling of its by-value copies; use __declspec(section .sdata2) on a non-const def

- status: works
- tags: sdata2,const,section,scheduling
- scope: RPGolFieldManager
- source: claude/golfield-data-1102

symptom: defining the 8-byte colour constants as const to land in .sdata2 dropped fn_80292068 from 100 to 70.9
cause: const-ness of the extern declaration changes the copy codegen
fix: keep extern GolShCol x; for the uses and define __declspec(section .sdata2) GolShCol x = {...}; section content and symbol size match, function stays 100
