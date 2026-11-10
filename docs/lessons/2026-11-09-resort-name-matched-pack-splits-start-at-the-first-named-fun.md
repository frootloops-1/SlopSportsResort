# resort: name-matched Pack splits start at the first NAMED function, not the file start

- status: works
- tags: resort,splits,RP,carve
- source: rp-drawpathmanager worker 2026-11-09

symptom: flip fails: multiply-defined ctor / undefined names; object has functions before the split
cause: carve_unk/port_splits take [first named hit, last named hit]; unnamed leading functions stay in the placeholder
fix: check the placeholder's first function against the object's first symbol (RPGrpDrawPathManager: scnProcDraw at 0x8024D2D0); extend the split back and absorb the placeholder
