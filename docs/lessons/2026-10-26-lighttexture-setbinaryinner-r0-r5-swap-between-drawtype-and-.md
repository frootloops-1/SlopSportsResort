# LightTexture SetBinaryInner r0/r5 swap between drawType and mask-hi is a register wall

- status: fails
- tags: eggLightTexture,SetBinaryInner,register-wall,IBinary,declaration-order
- scope: egg/gfxe/eggLightTexture
- source: claude/sbi-1026

symptom: SetBinaryInner 99.7: target lbz drawType->r5, clrrwi mask&0xFFFF0000->r0; ours swaps them (4 lines)
cause: graph-coloring order of two short-lived vregs; store order hi(0x42), drawType(0x48), lo(0x40) is fixed by source (stores are not reordered), so drawType cannot be sourced first
fix: none found: ~20 forms tried (hi local/no local, >>16<<16, & ~0xFFFF, u16 hi, (u16) lo casts, direct mDrawType=, int/u8 type locals, mask local in all decl orders, min as ternary/local max, loop without count). Best near-miss u32 mask; u8 type; first (L6 H0 correct, but type r7/mLightNum r5 swapped, 99.6). permute.py setup fails on mangled names containing <> (C stand-in parse error) -> permuter unusable for IBinary<T> methods without tool change
