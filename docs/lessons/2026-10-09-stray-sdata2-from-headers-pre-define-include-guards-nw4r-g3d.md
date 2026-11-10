# Stray .sdata2 from headers: pre-define include guards (NW4R_G3D_PLATFORM_GPU_H, EGG_GFXE_POST_EFFECT_BLUR_H)

- status: works
- tags: sdata2,include,cm2hw,g3d,blur,d7
- scope: RPGolMain

symptom: .sdata2 has leading cm2hw[4]+pad and 0xD7D7D7D7 literal, floats shifted, reloc-only mismatches
cause: static const cm2hw in g3d_gpu.h; BlurData::reset() GXColor{215..} pooled from eggPostEffectBlur.h even though unused
fix: #define NW4R_G3D_PLATFORM_GPU_H and #define EGG_GFXE_POST_EFFECT_BLUR_H before the includes; also shrink trailing symbol (size:0x8->0x4) in symbols.txt when the 4 extra bytes are alignment pad (sdata2 lbl_804C3EA0, sbss lbl_804BF850)
