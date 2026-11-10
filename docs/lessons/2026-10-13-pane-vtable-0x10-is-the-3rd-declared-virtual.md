# Pane vtable +0x10 is the 3rd declared virtual

- status: works
- tags: vtable,virtual
- scope: RPGol_802bca94
- source: sonnet-worker

symptom: slot offsets off by one
cause: 8-byte vtable header (RTTI+offset)
fix: v0,v1,v2 -> 0x8,0xC,0x10
