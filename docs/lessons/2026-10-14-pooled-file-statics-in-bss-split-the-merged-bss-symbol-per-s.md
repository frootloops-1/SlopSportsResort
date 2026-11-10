# Pooled file statics in .bss: split the merged bss symbol per static

- status: works
- tags: bss,symbols
- scope: RPGol_802b1a0c
- source: fn_802B4E60

symptom: reloc-name diffs ...bss.0 vs lbl_
cause: one dtk symbol covers several statics
fix: split symbols.txt bss symbol into one per static + non-static lbl_ global for trailing bytes
