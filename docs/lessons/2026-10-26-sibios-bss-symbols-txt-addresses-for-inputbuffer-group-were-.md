# SIBios bss: symbols.txt addresses for InputBuffer group were wrong

- status: works
- tags: SIBios,bss,symbols
- scope: revolution/SI/SIBios
- source: session 2026-10-26

symptom: SIBios bss 89%, SITransfer/GetTypeCallback 99.9 with ...bss.0 anchor vs Packet
cause: symbols.txt had InputBufferVcount/RDSTHandler/InputBuffer/InputBufferValid at 0x8047A580-A5C0; target code shows Packet+0x180/0x1a0/0x1b0/0x1c0 (0x8047A580/A5A0/A5B0/A5C0)
fix: set InputBuffer 0x8047A580, InputBufferValid 0x8047A5A0, InputBufferVcount 0x8047A5B0, RDSTHandler 0x8047A5C0; SIInterruptHandler 96.7 -> 97.1
