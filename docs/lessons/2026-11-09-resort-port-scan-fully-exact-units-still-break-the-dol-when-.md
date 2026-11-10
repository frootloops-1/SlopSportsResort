# resort: port_scan 'fully exact' units still break the DOL when the object has more code

- status: works
- tags: resort,porting,port_scan,layout
- scope: porting
- source: rescan 2026-11-09

symptom: 48 flipped units link but the DOL shifts (-8, -0x18...)
cause: port_scan only checks that Resort's named functions exist and match; ogws objects with extra functions/longer code (other library version) or missing Resort-only functions still score exact
fix: After ninja, tools/port_sizecheck.py PRE_FLIP_PORTED_JSON; drop units whose .text size differs, retry end-padding-only ones (<= 0xC smaller) with align:16 on the next split (kept 4 of 6)
