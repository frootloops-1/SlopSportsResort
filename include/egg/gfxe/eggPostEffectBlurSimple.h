#ifndef EGG_GFXE_POST_EFFECT_BLUR_SIMPLE_H
#define EGG_GFXE_POST_EFFECT_BLUR_SIMPLE_H
#include "eggPostEffectBase.h"
#include "types_egg.h"

namespace EGG {

class PostEffectBlurSimple : public PostEffectBase {
public:
    // Resort: 0x801B698C (the Wii Sports reset() body, inlined; blend mode 7)
    PostEffectBlurSimple();
    virtual ~PostEffectBlurSimple() {}  // at 0x8
    virtual void setMaterialInternal(); // at 0x10

public:
    // Field names are inferred from reset and material setup in RSPE01_01.
    // Resort offsets (ctor 0x801B698C).
    f32 mRadius;          // at 0x2C, normalized by the capture width
    GXColor mColor;       // at 0x30
    u8 mAlpha;            // at 0x34
    GXTevScale mTevScale; // at 0x38
    bool mUseTwoStages;   // at 0x3C
};

} // namespace EGG

#endif
