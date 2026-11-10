# SIBios bss gap is a split boundary, not a dummy object

- status: works
- tags: SIBios,bss,splits
- scope: revolution/SI/SIBios
- source: session 2026-10-26

symptom: bss 89%, SITransfer/GetTypeCallback 99.9 with anchor offset mismatch, pad_09_8047A3C0 0x40 before Packet
cause: the 0x40 before Packet is unowned zero bss; our object's .bss must start at Packet so anchor-relative immediates match
fix: splits.txt SIBios .bss start 0x8047A400; .bss 100, GetTypeCallback 100, SITransfer 100; DOL 0 bytes
