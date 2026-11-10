# Byte-struct constant in sdata2 split into four 1-byte dtk symbols: merge into one size-4 symbol (27E0 99.76 -> 100)

- status: works
- tags: rpgolplayermanager,symbols,sdata2,colour
- scope: RPGolPlayerManager
- source: orchestrator

symptom: relocs @sym+1..3 vs lbl_B9..BB
cause: symbols.txt over-split a 4-byte object
fix: keep lbl_804C42B8 size:0x4 align:4, drop B9/BA/BB
