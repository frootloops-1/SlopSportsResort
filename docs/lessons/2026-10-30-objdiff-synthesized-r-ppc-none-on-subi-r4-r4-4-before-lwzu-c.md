# objdiff synthesized R_PPC_NONE on subi r4,r4,4 before lwzu copy loop: rodata symbol at table-4

- status: works
- tags: objdiff,phantom,R_PPC_NONE,rodata,ptmf,symbols,RPSports_801E7EB4
- scope: Pack/RPSports/RPSportsCommon/RPSports_801E7EB4

symptom: asm_diff says identical but fn at 99.5%: objdiff marks 'subi r4,r4,0x4' (pre-decrement before lwzu loop) as DIFF_REPLACE with R_PPC_NONE to the symbol at table_addr-4 (lbl_80387004 / @stringBase0+476) in target only
cause: objdiff 3.8.2 infers pooled-address relocs from register tracking; target has a symbol at table-4 (alignment padding named lbl_ or previous TU-pool tail), ours has padding/section start
fix: symbols.txt/splits: drop padding lbl_80387004 (rodata is 8-aligned; prev TU ends 0x80387004) -> fn_801E90E4 100 (tested via objcopy --strip-symbol + objdiff-cli -1/-2). fn_801EA1C4 needs Main split into own TU (rodata 0x80387348..). Not fixable in source. Find it: objdiff-cli diff -p . -u main/<unit> -o x.json <fn>, print DIFF_REPLACE rows
