# F1 pool: 8-byte zero-pair target symbol with single lfs: declare extern const f32 sym[2], never define

- status: works
- tags: F1,pool,sbss2
- scope: RPGolUtlMtx
- source: claude/nm-data

symptom: RPGolUtlMtx fn_80295D28 99.74; defining all-zero const lands in .sbss2
cause: zero const goes to .sbss2
fix: extern const f32 lbl_804C3FB8[2] declaration only (data gap: our .sdata2 lacks the 8 zero bytes, code 100)
