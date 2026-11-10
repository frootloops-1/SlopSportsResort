# extern C array without initializer is only a declaration

- status: works
- tags: bss,extern,rpbsb
- source: RPBsb_80273950 2026-10-16

symptom: bss object missing in data_diff
cause: extern "C" T x[N]; declares only
fix: define inside extern "C" { T x[N]; }
