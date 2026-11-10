# RPBow_8031C388/8031EFE4: orphan string moved by rodata split, no R17

- status: works
- tags: rodata,split,string,stringBase0
- scope: RPBow_8031EFE4

symptom: 8031C388 carried 'const char lbl_803929C8[]' hack for BowExcelGlobal.bin that only fn_80320E00 of 8031EFE4 uses
cause: splits.txt gave .rodata 0x803929C8..E0 to the wrong unit
fix: move the .rodata line to RPBow_8031EFE4, symbols.txt lbl_803929C8 -> '@stringBase0 ... scope:local data:string_table', use the literal in fn_80320E00; 8031EFE4 .rodata 100, 8031C388 stays Matching, DOL 0
