# resort library: OSPlayRecord Block 4-aligned at +0x13C, compiler aligns to 8

- status: open
- tags: resort,library,port

symptom: 6-byte .bss offset diff
cause: Wii/1.0 aligns statics > ~0x80 to 8
fix: none yet
