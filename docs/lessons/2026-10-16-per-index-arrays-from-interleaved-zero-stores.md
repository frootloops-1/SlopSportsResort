# per-index arrays from interleaved zero stores

- status: works
- tags: struct,stores,rpbsb
- source: RPBsb_80283fe0 2026-10-16

symptom: zero stores at 0,8,0x10,0x12 then 4,0xC,0x11,0x13
cause: struct of 2-element arrays written unrolled per index
fix: cam[2],scr[2],a[2],b[2]; assign index 0 fields then index 1
