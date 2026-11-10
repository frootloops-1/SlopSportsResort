# pf_path sig {1,2} aggregate templates: right bytes, wrong 2-byte alignment

- status: open
- tags: pf_path,aggregate-init,sdata,sdata2,alignment,link-flip
- scope: revolution/VF/pf_path
- source: claude/nm-link-2 2026-10-15

symptom: pf_path flip: 34585 DOL bytes, .sdata 0x31 vs 0x30, no .sdata2 (orig 0x10); first moved l_dev_nandflash_init_info +8.
cause: Orig .sdata has no '~'/'1' strings; it holds one 01 02 00 00 template, and .sdata2 holds three 01020000 + pad, so the sig arrays are {1,2} aggregates padded to 4. Our hack loads bytes from string literals.
fix: Tried (L2): first sig non-const {1,2}, other three const {1,2}: .text unchanged, .sdata 0x2d, .sdata2 0x0a (templates packed at 2-byte alignment, orig 4); sig[4]={1,2}: .text +0x50 (word copy), worse. Untested: an aligned element type or __attribute__((aligned(4))) on the arrays; the '*.' vs '*.*' string also differs (orig '*.' at 0x10).
