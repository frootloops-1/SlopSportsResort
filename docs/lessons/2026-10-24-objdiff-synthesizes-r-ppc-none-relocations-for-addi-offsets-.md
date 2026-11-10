# objdiff synthesizes R_PPC_NONE relocations for addi offsets; read relocation names from objdiff JSON, not the ELF

- status: works
- tags: tooling,objdiff,reloc,data-ref
- scope: project
- source: claude

symptom: asm_diff says identical and both ELF reloc tables agree, yet a function is 99.9% (e.g. 'addi r4,r4,0x4d')
cause: objdiff tracks lis/addi bases and invents a relocation (target symbol containing base+imm); the ELF .rela has no such entry. proto3 JSON also omits zero addresses, so a symbol without 'address' is at offset 0, not undefined
fix: tools/data_fix.py runs 'objdiff-cli diff -u <unit> -o f.json <fn>' per function and aligns left/right instructions; undefined = no ELF symbol with that name and nonzero shndx. Ours-extern lbl_X indexed past dtk's size -> grow lbl_X over the following target symbols
