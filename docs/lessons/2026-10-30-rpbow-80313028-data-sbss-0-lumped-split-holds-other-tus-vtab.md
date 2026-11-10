# RPBow_80313028 .data/.sbss 0%: lumped split holds other TUs' vtables + jump table

- status: open
- tags: splits,data,sbss,RPBow,flip
- scope: Pack/RPSports/RPBowScene/RPBow_80313028
- source: claude/nm-3028-20261031

symptom: unit_cmp .data 0/.sbss 0 with SIZE-MISMATCH on many lbl_ objects although .text 99.95
cause: split .data 0x803CA1B8-0x803CA688 includes jumptable_803CA3E8 (fn_8031B3F4, RPBow_80319C98) and vtables keyed to later TUs; .sbss 998-A10 holds one 8-aligned chunk per TU
fix: own .data = 0x803CA1B8-0x803CA3B0 (defined in source as hand vtables), own .sbss = 0x804BF998-0x804BF9A0; needs orchestrator splits.txt change (+ lbl_804BF998 size 0x1) before any flip. Vtable owner = TU of its first (dtor) slot function, data order follows that
