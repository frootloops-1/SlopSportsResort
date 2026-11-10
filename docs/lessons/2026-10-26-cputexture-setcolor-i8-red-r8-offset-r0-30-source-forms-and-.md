# CpuTexture::setColor I8 red r8/offset r0: 30+ source forms and 10-min permuter no gain

- status: fails
- tags: eggCpuTexture,setColor,register,I8,permuter
- scope: egg/gfxe/eggCpuTexture
- source: claude/cpu-1026 opus

symptom: I8 case: red in r0 and offset in r6, target red r8 and offset r0 (99.6%, 8 lines); schedule identical
cause: pure colouring order residue: target colours offset before the red load; source decl order/position of the red load does not change it
fix: Failed: block-first temps (single-def temps get copy-propagated and reassociated to (buf+blk*32)+pix, 93.6), multi-def block var (flattens, 96.9), static inline offset/store helpers (same 8 lines), function-scope shared offset/pData (same), case order swap (65.7), % and / forms (84.6), getWidth()>>3 (94.3), u32 offset, const GXColor& alias, pData+=offset (94.5), red hoisted before switch (90.0); permuter 10 min best was RGBA8 dead-store noise, worse in verify (95.1). Only the reassigned offset var form keeps the target association.
