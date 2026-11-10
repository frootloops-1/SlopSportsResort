# Pre-define EGG_GFXE_POST_EFFECT_BLUR_H plus local reset()-free PostEffectBlur copy drops 0xD7D7D7D7 sdata2 word

- status: works
- tags: sdata2,header,guard,marker
- scope: egg/gfxe/eggShadowTexture
- source: shadow-1026

symptom: .sdata2 93.75: unreferenced @15859 = 0xD7D7D7D7 at pool start, retail has pad at 0x1c instead
cause: BlurData::reset() GXColor{215,215,215,215} literal in eggPostEffectBlur.h is pooled even when reset() is not emitted (including the header alone reproduces it)
fix: define the guard before includes, declare class PostEffectBlur locally without reset(); getBlurData needs '#line 102 "eggPostEffectBlur.h"' then '#line 1 "eggShadowTexture.cpp"' afterwards or assert file-name strings change (rodata drops to 96%). sdata2 100, no code change
