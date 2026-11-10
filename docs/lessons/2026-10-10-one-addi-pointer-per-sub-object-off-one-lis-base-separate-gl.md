# One addi pointer per sub-object off one lis base => separate globals, split the merged bss symbol in symbols.txt

- status: works
- tags: rpgol802a3a6c,bss,symbols,pool-relocations,savegpr
- scope: RPGol_802a3a6c
- source: opus

symptom: inline ctors/placement new on one struct fold to base+offset (24-67%); orig has _savegpr_27 and a pointer per object
cause: orig defines several separate globals pooled off ...bss.0; symbols.txt had one merged 0x118 symbol so pool relocs mismatch (96.57%)
fix: separate non-static globals + static inline Init helpers; Vec copy via u32[3] cast; one/zero locals declared 1.0 then 0.0; split lbl_804A8BB8 into 8 symbols -> 100%
