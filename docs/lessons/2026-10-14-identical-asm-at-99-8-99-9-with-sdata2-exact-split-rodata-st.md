# Identical asm at 99.8-99.9 with .sdata2 exact: split .rodata string-pool symbols

- status: works
- tags: rodata,strings,symbols
- scope: RPGol_802b020c
- source: fn_802B0310

symptom: addi rX,rX,off reloc mismatches into string pool
cause: symbols.txt splits one TU string pool into several labels
fix: merge into one lbl size=string bytes data:string_table; write strings as inline literals; own .sdata char* ptrs in the TU
