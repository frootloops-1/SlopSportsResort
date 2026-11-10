# ...data.0 anchor not at a preceding vtable means a TU boundary (RPBsb_8027a3c4 split at 0x8027A8DC)

- status: works
- tags: data,anchor,split,tu-boundary,vtable,rpbsb
- scope: Pack/RPSports/RPBsbScene/RPBsb_8027a3c4
- source: claude/flip-a3c4-20261031

symptom: fn_8027B020 99.9: lis/addi base ...data.0 vs target @518; the unit's .data starts with vtable lbl_803C6A20, then @518; defining 6A20 in the TU shifts the anchor offsets (99.8)
cause: MWCC's ...data.0 is always the TU's .data start (strong 6A20: anchor 0, offsets +0x50; weak, pool_data off or section(.data): no pooling, 79.4), so a retail base at @518 means 6A20 lives in another TU. 6A20's slots are only fn_8027A3C4..A87C, so the dtk unit was two TUs
fix: split splits.txt: 8027a3c4 = .text A3C4-A8DC + .data 6A20-6A48; new 8027a8dc = .text A8DC-B2D4 + ctors/.data 6A48-6B38/bss/sdata2; hand vtables (6AA0/6B0C behind defer_codegen off + extern first). Both 100%, DOL 0. General test: if a function's anchor base is a later object, look for a TU split at that object
