# CpuTexture setColor: class-level header changes and 4 more markers no gain

- status: fails
- tags: cputexture,setcolor,egg
- scope: egg/gfxe/eggCpuTexture
- source: 2026-10-29

symptom: setColor I8 red r0/offset r6 vs r8/r0 persists
cause: Colouring order unaffected by member/getter types or multi-def red
fix: none: mpBuffer u8*, getBuffer u8*, getWidth int, mWidth cast all 8 lines; u32 mFormat breaks 14 fns. Markers: identical-arm if for red 8, dead 'if(offset<0) r=color.r' 18, r=*(&color.r) 8, blk clamp (shape change). Park.
