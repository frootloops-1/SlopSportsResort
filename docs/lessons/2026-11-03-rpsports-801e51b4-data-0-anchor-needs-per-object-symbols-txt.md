# RPSports_801E51B4: ...data.0 anchor needs per-object symbols.txt split to reach objdiff 100

- status: works
- tags: 801E51B4,symbols,data.0,anchor,objdiff
- scope: RPSports_801E51B4

symptom: Code instruction-identical, DOL 0, but fn_801E5BF4 99.6% and unit 34/35: lis/addi reloc named ...data.0 vs lbl_803C2490, symbol sizes 0xB8/0x30
cause: dtk lumped four static pointer tables into two lbl_ symbols; TU anchor label ...data.0 missing
fix: symbols.txt: add ...data.0 = .data:0x803C2490 label local; split lbl_803C2490 0xA0 + lbl_803C2530 0x18; lbl_803C2598 0x14 + lbl_803C25AC 0x1C; all four scope:local. Then 35/35, all sections 100, DOL 0.
