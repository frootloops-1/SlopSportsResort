# TRKDoSetOption: single contiguous char array with s, s+0x20, s+0x28 also folds to mr

- status: fails
- tags: TRK,msghndlr,addi,mr,L1
- source: xfer-1028

symptom: 98.8, addi r3,r31,0 vs mr r3,r31
cause: Array decay of offset 0 is still folded to a register copy; target string offsets 0/0x20/0x28 rule out a plain -str pool (packed 0/0x1f/0x27)
fix: none; 4th session on this. Do not retry pointer or array spellings; next idea would be a different object boundary (strings inside a larger data object whose base is not the string)
