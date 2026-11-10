# Packed IBinary Bin: separate 0x20 struct members, not one array

- status: works
- tags: egg,ibinary,struct-copy
- scope: egg/gfxe
- source: claude/gfxe-1021

symptom: Get/SetBinaryInner copies via ctr loop or wrong spill order
cause: a 0x60 array member is copied with a loop; three 0x20 members unroll to lwz/stw pairs
fix: model Bin data as separate sub-struct members (DrawPathBloom GetBinaryInner 67->100)
