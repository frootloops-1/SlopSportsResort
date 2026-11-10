# CpuTexture::setColor I8 branch: color.r direct / single-expression index forms no gain

- status: fails
- tags: eggCpuTexture,setColor,register,I8
- scope: egg/gfxe/eggCpuTexture

symptom: I8 case: red byte lands in r0 and pixel offset in r6, original has red in r8 and offset in r0 (99.60%)
cause: register coloring residue; unresolved
fix: Tried (a) drop u8 r local, use color.r directly with offset += block*32 (99.6, same); (b) one-line buffer[(x&7)+(y&3)*8+tile*32]=color.r (93.6, swaps this/x regs, worse). Combined with earlier handoff attempts, source-form levers are exhausted.
