# fn_801FAF28 sdata2 1.0f: target lbl_ symbol 8B (1.0f + alignment tail) vs our 4B @N

- status: works
- tags: sdata2,symbols,pool
- scope: RPSports_801f9150
- source: claude/d3-1028

symptom: fn_801FAF28 99.99%, instruction-identical, only lfs reloc lbl_804C20E8 vs @3249
cause: dtk sized lbl_804C20E8 as 8B (1.0f plus 4B zero alignment tail up to unit end), so pool_renames could not pair it with our 4B pool entry
fix: symbols.txt: lbl_804C20E8 -> @3249 size 4 scope:local + gap_12_804C20EC_sdata2 size 4; rerun dtk split. DOL 0 bytes.
