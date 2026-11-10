# Nested sport/mode switch: volatile game read declared after mode fixes r0/r4 colour swap (R17)

- status: works
- tags: switch,regalloc,volatile,forward-substitution,RPSports_801ffec0
- scope: Pack/RPSports
- source: claude/sp801ff-1103

symptom: lwz r0,0x54 / lwz r3,0x48 vs retail lwz r4,0x54 / lwz r0,0x48 for switch(game){case: switch(mode)}
cause: game is forward-substituted into the switch expression and gets a fresh high temp vreg (coloured first, takes r0); decl order, holder pointer, inline getter for mode, inline switch helper, & 0xFFFFFFFF all leave it
fix: s32 mode; s32 game; ... game = *(volatile s32*)(lbl_804BF730+0x54); mode = ...; switch(game): game declared after mode (lower vreg, coloured later). fn_80200D38 + fn_801FFFBC 99.6 -> 100, ledger 155/156
