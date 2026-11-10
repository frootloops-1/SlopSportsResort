# Local VEC3 arrays always 8-aligned on stack

- status: fails
- tags: egg,stack,alignment
- scope: egg/gfxe
- source: claude/gfxe-1021

symptom: ModelBoundingInfo::calc frame 0x10 too big, setMin at 0xd30 vs 0xd2c
cause: MWCC 8-aligns local VEC3 arrays
fix: dead end: struct wrap, raw f32 array, aligned(4), declaration order all failed
