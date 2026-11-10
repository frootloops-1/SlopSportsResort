# Flip short: tables reached only by base+offset are dead-stripped

- status: works
- tags: linker,deadstrip,force_active,data,flip
- scope: RPBoxScene
- source: RPBox_802e2a84 2026-11-07

symptom: flip_gate DOL short by N bytes after asm conversion; nm shows local tables missing
cause: asm bodies address local tables as base+offset (no reloc to them), so the linker strips the unreferenced locals
fix: wrap their definitions in #pragma push / #pragma force_active on / #pragma pop
