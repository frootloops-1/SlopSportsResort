# Split string pool symbols cause phantom addi reloc mismatches

- status: works
- tags: rodata,string,stringBase,symbols
- scope: RPGol_802c6e28
- source: claude/rpgolscene-unsplit

symptom: instructions identical, objdiff <100 on addi rX,rX,0xNN after lis/addi of a string pool base
cause: symbols.txt splits one MWCC @stringBase0 pool into several lbl_ objects; objdiff resolves base+off against them
fix: merge the pool into one symbols.txt string object (size = string bytes, pad absorbed); use inline literals in first-use order (sdata pointer inits declared first)
