# C objects with extab need -Cpp_exceptions on

- status: works
- tags: msl,extab,link
- scope: MSL_C, any C unit with extab
- source: claude/msl-text 2026-10-09

symptom: Object .text matches 100% but the linked DOL fails (ok target) and dtk dol diff reports shifted extab symbols
cause: Original MSL_C objects were compiled with exceptions enabled, so they carry extab/extabindex entries; our default -Cpp_exceptions off emits none, shrinking the section and shifting everything after it
fix: Add extra_cflags=['-Cpp_exceptions on'] to every Object whose splits.txt entry has extab/extabindex; objects without extab stay off. Objdiff .text 100% is not enough: run ninja and check main.dol: OK
