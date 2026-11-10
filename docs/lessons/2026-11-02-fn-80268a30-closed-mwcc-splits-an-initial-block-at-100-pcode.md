# fn_80268A30 closed: MWCC splits an initial block at ~100 pcodes; dead abstract-base vtable store supplies the missing pcodes

- status: works
- tags: block-split,pcode,vtable,abstract-base,RPBsb_802656a4,symbols,sbss
- scope: RPBsb_802656a4 fn_80268A30

symptom: li r3,0x68 sits ~8 insns later than retail in a long unrolled inline-ctor block (99.2%)
cause: Initial pcode generation splits a basic block once it reaches ~100 pcodes (checked per statement); the pre-RA scheduler cannot move across the split. Retail's inline state ctor stored the abstract base's all-zero (all-pure) vtable first, then the derived vtable; the backend deletes the dead store but its 3 pcodes/iteration still count. lbl_803C5D30 is 0x28 = derived vtable (5) + zero base vtable (5) at +0x14.
fix: In the inline ctor: vtbl = lbl_803C5D44; vtbl = lbl_803C5D30; (D44 = base vtable, own symbol: lbl+5 / &lbl[5] costs an extra addi pcode and over-splits). symbols.txt: split lbl_803C5D30 to 0x14 plus lbl_803C5D44 0x14; 12 local ptmf consts @2352..@2363 replace lbl_803C5C48. Keep lbl_803C5D30[10] defined in source (an all-zero lbl_803C5D44[5] definition goes to .bss even with __declspec(section .data)); D44 stays an extern with no reloc. Also the sbss gap must be u16 + u8[4], not u8[6] (MWCC aligns a 6-byte array to 4, growing .sbss and shifting later symbols by 8). Measure with mwcc_dbg backend block sizes. Candidate: the R17 dead duplicate vt2c store in RPBsb_80268f8c fn_80269DF4 may be the same mechanism.
