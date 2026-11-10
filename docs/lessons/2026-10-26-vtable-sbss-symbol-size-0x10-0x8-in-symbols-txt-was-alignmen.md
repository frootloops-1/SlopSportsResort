# Vtable/sbss symbol size 0x10/0x8 in symbols.txt was alignment padding

- status: works
- tags: symbols,vtable,sbss,size,padding
- scope: Pack/RPGraphics
- source: claude/data-grp-1026

symptom: unit_cmp SIZE-MISMATCH vt 16!=12 and spCurrent 8!=4 with all code 100%
cause: symbols.txt sizes include padding to the next 8-aligned object
fix: set size:0xC and size:0x4 then dtk dol split --no-update; dtk adds hidden gap_ symbols, unit sections 100%. RPGrpModelResManager has the same pattern
