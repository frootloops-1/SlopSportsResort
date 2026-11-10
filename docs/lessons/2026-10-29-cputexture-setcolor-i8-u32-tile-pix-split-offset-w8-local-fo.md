# CpuTexture setColor I8: u32 tile/pix split, offset+=, w8 local forms no gain

- status: fails
- tags: cputexture,setcolor,egg
- scope: egg/gfxe/eggCpuTexture
- source: 2026-10-29

symptom: setColor I8 red r0/offset r6 vs target r8/r0, 8 diff lines
cause: Same expression-temp vs named-def colouring order; spelling does not move it
fix: none: u32 tile+pix single store (40 lines), offset += block*32 with deref store (8 lines), u16 w8 local (42 lines). Do not retry; only class-level or marker approaches remain.
