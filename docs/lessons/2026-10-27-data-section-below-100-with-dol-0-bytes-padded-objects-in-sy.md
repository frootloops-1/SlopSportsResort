# Data section % below 100 with DOL 0 bytes: padded objects in symbols.txt

- status: works
- tags: symbols,sdata,data,bss,rodata,padding
- scope: egg/core/eggController
- source: claude/controller-1027

symptom: unit_cmp shows .sdata 66.67/.rodata 99.2/.bss 99.35 and SIZE-MISMATCH (8!=4, 16!=12, 424!=417) although DOL diff is 0
cause: dtk symbols.txt sizes include alignment padding (next unit's 8-align / tail pad), our .o objects are the real size; unsized lbl_ pool names differ from @stringBase0
fix: set size to the real object size (padding becomes gap_ symbol), rename lbl_ string pool to @stringBase0 scope:local with real size, rerun dtk dol split --no-update; objdiff then pairs @N temps by content. eggController all sections 100
