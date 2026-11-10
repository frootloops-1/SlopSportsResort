# TU split RPSports_801eb388 @0x801EC3C0 -> 801ec3c0 Matching; delete global gap_ data symbol at TU end

- status: works
- tags: tu-split,splits,vtable,literals,RPSports_801ec3c0
- scope: RPSports_801ec3c0

symptom: combined unit rodata 0, data 9.78, sbss 0, sdata2 50; fn_801EC510 99.7
cause: two TUs in one split (title scene + training menu); TU2 table read by TU1 must be global in TU2
fix: split + literals + const struct table + hand vtables (R17 114/115); delete gap_08_803C278C_data (regenerated hidden) -> .data 100; shrink .sbss symbols to 0x4. fn_801EC034 stays 100-rounded with int->float slot diff (retail 0x48,0x48|0x50,0x50).
