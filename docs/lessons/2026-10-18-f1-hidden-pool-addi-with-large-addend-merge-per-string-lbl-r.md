# F1 hidden+pool addi with large addend: merge per-string lbl_ rodata symbols into one string_table symbol

- status: works
- tags: F1,symbols,rodata,string_table
- scope: RPSysLytMenuFrame,RPSysLytPlayerSelect
- source: claude/nm-data

symptom: code identical but addi rX,rY,0x346 scores <100 (hidden+pool); target reloc is lbl_80384E07+0x7f, ours lbl_80384B40+0x346
cause: per-string lbl_ symbols in symbols.txt make dtk synthesize relocs to the containing string symbol
fix: merge lbl_ strings into one symbol covering the pool (keep the name src externs), data:string_table; RPSysLytMenuFrame 5 fns to 100
