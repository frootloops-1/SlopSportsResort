# Pre-define g3d_gpu/post_effect_blur include guards to drop sdata2 cm2hw pad; TBitFlag u8 truncation

- status: works
- tags: sdata2,include-guard,cm2hw,tbitflag
- scope: Pack/RPKernel

symptom: .sdata2 has leading cm2hw + 0xD7D7D7D7; constants reloc-only mismatches
cause: headers pull g3d_gpu.h / eggPostEffectBlur
fix: #define NW4R_G3D_PLATFORM_GPU_H and EGG_GFXE_POST_EFFECT_BLUR_H before includes. For or/andc+clrlwi 24+stw: keep setBit/resetBit then flag=static_cast<u8>(flag)
