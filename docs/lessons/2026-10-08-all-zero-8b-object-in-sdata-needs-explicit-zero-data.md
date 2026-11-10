# All-zero 8B object in .sdata needs explicit_zero_data

- status: works
- tags: sdata,pragma

symptom: zero object lands in .sbss
cause: MWCC puts zero-init in bss
fix: #pragma explicit_zero_data on around definition
