# CpuTexture setColor: 11 steering-construct variants (dead copies, identical-arm ternaries, hoisted locals) no gain

- status: fails
- tags: cputexture,setcolor,marker,steering
- scope: egg/gfxe/eggCpuTexture

symptom: setColor I8 red r0 vs r8, offset r6 vs r0 (8 lines baseline)
cause: dead/copy/identical-arm constructs are optimised away before colouring (8 lines unchanged); constructs that survive change the instruction stream (w local 10 lines, tile-local 40). regsearch score 'setColor' substring picks a different overload: score via verify.py + asm_diff with the full mangled name instead
fix: none: tried dummy blk split, offset=offset?offset:offset, pData?color.r:color.r, offset copy, const u8* to color.r, red after ptr, u16 w local, buf local first/after, tile local (x2). Source restored; no marker added. Next hypothesis needs a surviving IR change (header getBuffer/getWidth bodies or GXColor param type)
