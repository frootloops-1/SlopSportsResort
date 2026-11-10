# resort: +0x28 DOL shift after a flip = a weak function still fn_-named elsewhere, so the linker keeps both copies

- status: works
- tags: resort,weak,dedup,flip,symbols
- source: rp-drawpathmanager-2 worker 2026-11-09

symptom: flip_gate shifts everything after the unit by the weak functions' size
cause: the object's weak copy only dedups against an earlier copy with the same name
fix: rename the earlier fn_ copy (RPGrpDrawPath::On/Off at 0x801CF84C/0x801CF838)
