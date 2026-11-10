# regalloc_diag: callee-saved register order is not predicted by uses/span/def position; diagnose per moved value

- status: works
- tags: regalloc,forecast,tooling
- scope: tools/regalloc_diag.py
- source: docs/forecast-regalloc-notes.md

symptom: Forecast notes claim call-live values are ordered by spill weight; unverified on our build
cause: Measured 918 target functions: uses 0.44, span 0.51, first-def 0.45 concordance (random); weak signals only: params lower reg 64%, earlier-dying values higher reg 62%
fix: tools/regalloc_diag.py names the moved value(s) and levers (4 of 5 retro cases agree with the lever that worked; fn_801E8ED0 needed an inline accessor, now hinted). 125 REGALLOC near-misses: 47 volatile-only, 23 value-placement, 15 order, 37 split ranges.
