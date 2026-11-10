# RPBsb_80283974: phantom addi on string pool fixed by merging symbols.txt pool into one object

- status: works
- tags: rodata,symbols,addi,strings
- source: RPBsb_80283974

symptom: fn at 99.8, asm_diff identical; addi from @stringBase0 base vs split lbl_8038D808 size 0xD
cause: symbols.txt split a TU's string pool into small symbols
fix: merge lbl_8038D808..D87D into one data:string object size 0x238 (TU split end); dead static fn defined LAST pools unreferenced middle strings; switch with early-return case 0: if(kind==0)return; switch(1..3)
