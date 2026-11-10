# RPGrpModelRfl BSS order fixes seven linked bytes despite 100 percent data scores

- status: works
- tags: RPGrpModelRfl,bss,layout,DOL
- scope: RPGrpModelRfl

symptom: Temporary Matching link differed by 19 bytes in DrawGX, Configure, static init and RPSysKokeshiManager; sDrawCoreSetting linked 48 bytes early.
cause: All-zero BSS compares as 100 percent while symbol order differs: compiled setting at offset 0 and matrix at 0x28; retail matrix at 0 and setting at 0x30.
fix: Move sDrawCoreSetting definition below lbl_804A4608 matrix. Temporary Matching DOL now differs by 12 bytes only in DrawGX; symbol checker has only three existing collisions. Keep NonMatching: DrawGX scheduling still 99.7 percent.
