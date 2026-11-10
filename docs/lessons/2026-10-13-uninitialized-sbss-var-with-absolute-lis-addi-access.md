# Uninitialized .sbss var with absolute (lis/addi) access

- status: works
- tags: mwcc,sbss,sdata,pragma,metrotrk
- scope: MetroTRK/mainloop
- source: 2026-10-13

symptom: Original has a var in .sbss but accessed via lis/addi; -common on or declspec(section .sdata) give wrong section/sda21 and break dol hash
cause: -sdata 0 normally means .bss/abs; declspec .sdata gives .sbss but sda21 addressing
fix: #pragma section RW ".sdata" ".sbss" data_mode=far_abs then __declspec(section ".sdata") T var; (no -common flag). mainloop.c now Matching
