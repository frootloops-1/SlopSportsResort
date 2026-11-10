# Trailing 0.0f in a TU .sdata2 symbol can be TU pad; shrink symbol size

- status: works
- tags: sdata2,symbols,padding
- scope: RPTns_8022c1d0
- source: claude 2026-10-14

symptom: .sdata2 90.91%: last literal symbol size 0x8 ends in an unreferenced 0.0f
cause: dtk sized the last pooled literal over the 8-byte TU alignment pad
fix: set the symbol size to 0x4 in symbols.txt; the next TU .sdata2 is 2**3 aligned so DOL stays OK (RPTns_8022c1d0 lbl_804C28F8)
