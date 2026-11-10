# Shared-base GXSetArray tables: file-scope static arrays named lbl_* + split symbols scope:local

- status: works
- tags: rodata,static,symbols
- scope: mwcc
- source: RPTns_802390b0

symptom: orig lis/addi r31 once then addi r4,r31,0x40; global array gives per-call lis/addi; function-local statics get name$NNN and .rodata 99%
cause: MWCC addresses statics via one section base; function-local statics are renamed with $N so objdiff cannot pair them
fix: file-scope static const s16 lbl_8038B940[] ALIGN(32) etc.; symbols.txt split the 0xB0 blob into 3 scope:local align:32 objects
