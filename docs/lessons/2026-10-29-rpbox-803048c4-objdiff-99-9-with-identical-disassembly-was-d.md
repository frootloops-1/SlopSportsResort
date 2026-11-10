# RPBox_803048c4: objdiff 99.9 with identical disassembly was .data order; define lbl_803C9C08 before the string tables

- status: works
- tags: RPBox_803048c4,data-order
- scope: RPBox

symptom: fn_80304B58 stuck at 99.9 with identical asm; two addi mismatches
cause: objdiff resolved addi r25,r28,0x40 / addi r25,r25,4 to the wrong data symbol because our .data had the vtable after the string tables
fix: Move lbl_803C9C08 definition before lbl_803C9C18/lbl_803C9C58: 99.9 -> 100
