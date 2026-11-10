# Per-string rodata symbols block string reloc/data matches

- status: works
- tags: rodata,strings,symbols
- scope: RPGol_802b6a58
- source: opus-worker

symptom: asm identical but fn 99.9, .data 87.5, .rodata 98
cause: MWCC pools strings into one @stringBase0; symbols.txt had 5 per-string lbl_ plus pad in last size
fix: merge into one lbl_ symbol sized to the pool (exclude TU-end pad), drop the rest
