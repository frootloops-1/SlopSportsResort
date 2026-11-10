# Pre-define header guards NW4R_G3D_PLATFORM_GPU_H EGG_GFXE_POST_EFFECT_BLUR_H; sdata2 GXColor local = one 4-byte symbol; rodata pool @stringBase0

- status: works
- tags: sdata2,symbols,include
- scope: RPTns_802318a4
- source: claude/rptns-2

symptom: sdata2 85.7% (cm2hw, 4 one-byte colour symbols, last symbol incl TU pad); rodata 99.05%
cause: symbols.txt had 4 one-byte colour syms, lbl_804C2AD8 size 8 incl TU pad, rodata pool lbl_8038B6E8 size 0x140 incl 6 pad bytes
fix: symbols: lbl_804C2AB8 size 0x4 (drop ABA..ABB), lbl_804C2AD8 size 0x4, @stringBase0 = .rodata:0x8038B6E8 size:0x13A scope:local data:string_table -> rodata/sdata2/data 100%
