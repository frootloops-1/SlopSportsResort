# RPGolConfig state test register wall remains R17

- status: fails
- tags: RPGolConfig,regalloc,bool,inline,R17
- scope: fn_8029D3AC
- source: docs/marker-ledger.md

symptom: 35 same-shaped instructions at 98.57143% with m and boolean GPRs permuted
cause: Named/inline boolean local allocation differs; all six compilers tie
fix: Prior 15 declaration/type variants plus 32 additional int/long/bool, pointer-const and inline state-helper variants did not close. Native symbolic assembly equals 140 raw bytes and one relocation; marker row 225, earlier C++ retained.
