# Multi-dim table read: index through inline cast of the global, not a local T*

- status: works
- tags: array,addressing,stfsux,table
- scope: RPTns_802194f8
- source: opus worker 2026-10-14

symptom: address terms grouped differently (93%), extra saved reg
cause: local typed pointer regroups index arithmetic
fix: ((const T(*)[3][3][3])global)[i0][i1][i2][i3]; copy into dst=&D[..] field-by-field for stfsux; brute-force loop var names if counters misnumbered (fn_8021958C)
