# Last RPBow data: jumptable_ name and padded float size

- status: works
- tags: data,jumptable,symbols,size
- scope: Pack/RPSports/RPBowScene
- source: session-2026-11-07

symptom: RPBow_80319C98 .data 77%, RPBow_803381DC .sdata2 99%
cause: objdiff pairs data by name: jumptable_803CA3E8 vs compiled @1915; lbl_804C6388 size 8 included 4 B trailing pad
fix: rename to @1915; size 0x4. All units data 100%
