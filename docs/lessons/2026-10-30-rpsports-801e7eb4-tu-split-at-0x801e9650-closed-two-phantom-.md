# RPSports_801E7EB4 TU split at 0x801E9650 closed two phantom-reloc fns and flipped the Main half

- status: works
- tags: tu-split,splits,rodata,phantom,R_PPC_NONE,sbss,RPSports_801E7EB4,RPSports_801e9650
- scope: Pack/RPSports/RPSportsCommon/RPSports_801e9650
- source: worker 2026-10-31

symptom: fn_801E90E4/fn_801EA1C4 99.x with identical code (phantom R_PPC_NONE on subi before lwzu copy), .rodata order wrong, .sbss 8!=4
cause: Main controller is its own TU after the PS @stringBase0; lbl_80387004 was 8-align padding; lbl_804BF710 size included sbss pad
fix: splits: PS text ..0x801E9650, rodata 0x80387008-0x80387348; new RPSports_801e9650 text 0x801E9650-0x801EA458, rodata 0x80387348-0x80387438, sbss 0x804BF710-0x804BF718; drop lbl_80387004; lbl_804BF710 size 4; source split by halves (PS externs singleton). Both fns 100, Main half Matching at DOL 0. Remaining PS .sdata2 96.3 = explicit global gap_12_804C1F2C/4C pad symbols in symbols.txt
