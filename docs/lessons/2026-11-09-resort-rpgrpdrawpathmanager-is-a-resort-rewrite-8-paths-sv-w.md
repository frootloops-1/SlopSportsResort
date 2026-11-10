# resort: RPGrpDrawPathManager is a Resort rewrite (8 paths, SV with bool, extra priority method)

- status: works
- tags: resort,RP,DrawPathManager
- source: rp-drawpathmanager-2 worker 2026-11-09

symptom: 11/27 after the full-file split
cause: Resort rewrote the manager
fix: rebuilt from asm: paths 0x18-0x38, flags 0x04/0x10/0x20/0x40/0x80, timing table from rodata; out-of-line ScnRenderer accessors as placeholders; 27/27
