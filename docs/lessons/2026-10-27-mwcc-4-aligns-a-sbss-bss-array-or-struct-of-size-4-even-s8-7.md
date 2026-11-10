# MWCC 4-aligns a sbss/bss array or struct of size >=4 (even s8[7]); model trailing padding as scalars <=2 bytes

- status: works
- tags: flip,sbss,alignment,padding,RPBsb_80263eec
- source: RPBsb_80263eec 6b2287210

symptom: Flip gives ~1.9k DOL diff bytes at equal total size; built .sbss is 0xb vs 0x8 in the dtk split object; sym_addr_check shows a later sbss symbol shifted +8.
cause: Source defined s8 lbl_804BF7D9[7] in .sbss; MWCC 4-aligns it (even under pragma pack), inserting leading padding.
fix: Define it as s8 plus padding scalars (s8,s8,s16,s16) so .sbss is exactly 8 bytes. Follow-up: symbols.txt still lists lbl_804BF7D9 size 0x7 vs source 1, so unit_cmp shows .sbss 56%; DOL is 0 diff.
