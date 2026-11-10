# resort: RPSysProjectLocal has no pack ID or sound storage

- status: works
- tags: resort,rp

symptom: field offsets off
cause: Resort layout
fix: locale 0xC, language 0x10, frame rate 0x14, flags 0x18; EArea gains Unk8/Unk9
