# Hand-defined string blob keeps lbl_ pool name: .rodata 0 -> 100 without symbols.txt edits

- status: works
- tags: rodata,string-pool,R17,RPBow
- scope: Pack/RPSports/RPBowScene/RPBow_80313028
- source: claude/nm-3028-20261031

symptom: .rodata 0: extern lbl_803921D4 string table + lbl_80392190 name table never emitted
cause: dtk named the -str pool lbl_ (global); literals would emit @stringBase0 which objdiff does not pair
fix: extern const char lbl_803921D4[0x2CC] = octal-escaped pieces (incl. dead folded assert strings), then extern const table = {{lbl + off}} declared before; code bytes unchanged. Generator: dump .string lines from the unit asm. R17 + ledger row
