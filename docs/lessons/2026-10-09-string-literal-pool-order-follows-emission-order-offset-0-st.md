# String-literal pool order follows emission order; offset-0 string changes regalloc

- status: open
- tags: RPGolFieldManager,rodata,strings

symptom: fn_80293008 98.3% with literals; 99.2% with original pool order (instructions identical)
cause: CW pools literals in code-emission order (ascending addr = reverse of descending source); string at pool offset 0 shares base reg
fix: needs unit-level pool: all fns as literals + .sdata/.data string pointers; maybe symbols.txt @stringBase0 table
