# Rodata diff after a pool = missed TU boundary: 8-aligned global right after the @stringBase0 pool belongs to the next unit

- status: works
- tags: flip,rodata,splits,boundary,RPSports_801f8750
- scope: RPSports_801f8750
- source: orchestrator-1027

symptom: RPSports_801f8750 .rodata 98.11 with 35/35 syms exact; dtk .o has the pool ending at 0xC4, a 4-byte gap, then 12-byte global lbl_803885B8 (cpuData.bin) at 0xC8
cause: splits.txt boundary one 8-aligned symbol too far; the string is not pooled and not in this TU
fix: Move .rodata boundary 0x803885C8 -> 0x803885B8 (also in the previous unit), define the string in RPSports_801f9150 (next unit), drop the definition here. DOL 0; neighbour not regressed. Diagnose with objdump -s -j .rodata of built vs dtk .o. 801ff94c is a different problem (emission order).
