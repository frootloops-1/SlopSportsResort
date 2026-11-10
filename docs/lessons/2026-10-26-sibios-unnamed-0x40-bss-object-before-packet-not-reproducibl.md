# SIBios: unnamed 0x40 bss object before Packet not reproducible by an unused static

- status: fails
- tags: SIBios,bss,pad
- scope: revolution/SI/SIBios
- source: session 2026-10-26

symptom: our Packet at .bss offset 0; target Packet at +0x40 with pad_09_8047A3C0_bss before it
cause: a 0x40 static that nothing references is dropped by MWCC, even with force_active on
fix: none yet; need a referenced 0x40 object or a different source of the pad
