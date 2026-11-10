# F1 jumptable/data owned by another unit's split cannot be fixed by renaming: dtk exports local as @N_<addr>

- status: fails
- tags: F1,jumptable,splits
- scope: RPBow_803433E4,RPBow_80335DB0,RPBow_8032ADD8,RPBowNpcManager
- source: claude/nm-data

symptom: fn_80344A6C/fn_8033763C/fn_8032EB10 99.9x%, jumptable_803CAxxx lives in RPBow_80313028 .data; RPBowNpcManager rodata/data in other splits
cause: table/data outside the unit's own splits
fix: needs a splits.txt change moving the jump tables / 0x80392C30 rodata / 0x803C3FC0.. data into the owning units
