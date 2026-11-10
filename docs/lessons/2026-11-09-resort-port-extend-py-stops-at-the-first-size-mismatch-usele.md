# resort: port_extend.py stops at the first size mismatch; useless when Resort's weak helpers differ

- status: fails
- tags: resort,tools,port_extend,RP
- source: rp-drawpathmanager worker 2026-11-09

symptom: port_extend renames only the leading functions
cause: Resort's version has extra/non-inlined helpers (RPGrpDrawPathManager 0x8024D5DC-0x8024D8D0)
fix: map by hand: match non-weak functions and the dtor run at the file end by size/code, confirm with verify.py
