# asm2cw: whole-function asm from dtk .s, pool via asm float literals

- status: works
- tags: asm,R17,tool,pool,jumptable,force_active
- scope: RPBoxScene
- source: RPBox_802e2a84 2026-11-07

symptom: converting non-exact functions to whole-function asm by hand is slow; pool @NNN can't be named from asm
cause: dtk asm syntax differs from CW inline asm; compiler literals are anonymous
fix: python3 tools/asm2cw.py <unit> <fn> --apply src/<unit>.cpp: lfs/lfd of @NNN become asm float literals (share the C pool), sda externs typed int (char[] gives ADDR16), qrN->N, jump tables hand-made
