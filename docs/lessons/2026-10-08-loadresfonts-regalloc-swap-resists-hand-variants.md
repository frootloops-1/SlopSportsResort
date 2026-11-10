# LoadResFonts regalloc swap resists hand variants

- status: fails
- tags: regalloc,permuter,RPSysFontManager
- scope: Pack/RPSystem/RPSysFontManager LoadResFonts
- source: docs/tasks/RPSysFontManager.md, 2026-10-08

symptom: LoadResFonts stuck at 99.07%; Opus tried 12 hand variants, none better (definition-before-caller, GetResFont accessor, ResFontType param, all-enum indexing, pointer-arith slot, late ref decl, no data local, chained assign, explicit inline).
cause: Probably register-allocation order; not confirmed.
fix: Do not repeat these 12 by hand. Run tools/permute.py (see docs/permuter.md) or check per-file pragmas and compiler build.
