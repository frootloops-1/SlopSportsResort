# Phantom R_PPC_NONE / addi addend past symbol end: merge the adjacent split rodata symbols

- status: works
- tags: data-ref,rodata,symbols,string-pool
- scope: project
- source: claude

symptom: asm_diff says identical but percent <100; an 'addi rX,rX,0xNN' is flagged (hidden+pool)
cause: dtk split a string pool into several lbl_ symbols; the compiler's addend steps past the end of the first one
fix: merge the split lbl_ symbols in symbols.txt into one covering the whole pool (@stringBase0 ... data:string_table, size = string bytes only, or one lbl_ when the source defines the array) - 8 of 8 tried (RPBsb_8024e334, ButtonA, RPBox_802de63c/802e2a84/802f438c, RPSports_801ea458/801eb388). Grep src/ and include/ for the old lbl_ name first
