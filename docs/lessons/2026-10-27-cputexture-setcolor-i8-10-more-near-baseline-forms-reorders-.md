# CpuTexture setColor I8: 10 more near-baseline forms (reorders, u32 r, u16 offset, pData[offset], *pData) no gain

- status: fails
- tags: eggCpuTexture,setColor,register
- scope: egg/gfxe/eggCpuTexture
- source: claude/cpu2-1027 sonnet

symptom: I8 red r0/offset r6 vs target r8/r0, 8 diff lines
cause: coloring-order residue, unchanged by decl order or store spelling
fix: Tried red-after-pixel decl, u32 r, pData[offset], *pData, % forms: baseline 8 lines or much worse (38-45, this/x regs swap). Remaining 6 DOL bytes are the only gap for the unit.
