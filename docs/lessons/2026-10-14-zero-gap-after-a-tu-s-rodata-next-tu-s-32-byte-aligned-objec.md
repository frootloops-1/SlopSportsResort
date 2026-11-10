# Zero gap after a TU's .rodata = next TU's 32-byte aligned object

- status: works
- tags: rodata,alignment,splits,dol
- scope: RPTns_802383b4
- source: claude 2026-10-14

symptom: unit 100% but DOL FAILED; .rodata 0x10 short; target TU has gap_ zero fill to a 0x20 boundary
cause: next TU's first .rodata object is align 32; dtk folded the pad into the previous TU
fix: shrink previous TU's splits.txt .rodata end to its 8-aligned size and add align:32 to the next object's symbol (8038B940)
