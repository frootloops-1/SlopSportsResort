#ifndef EGG_GFXE_POST_EFFECT_SIMPLE_H
#define EGG_GFXE_POST_EFFECT_SIMPLE_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggPostEffectBase.h>

namespace EGG {

class PostEffectSimple : public PostEffectBase {
public:
    // Resort: 0x801B77D8 (unnamed in symbols.txt)
    PostEffectSimple();
    virtual void reset();               // at 0x14
    virtual void setMaterialInternal(); // at 0x18

public:
    enum EBlendMode {
        //! Color blends with framebuffer
        cBlendMode_Opa,
        //! Color blends with framebuffer where texture is visible
        cBlendMode_Xlu,
        //! Color blends with framebuffer, texture alpha controls intensity
        cBlendMode_Intensity,
    };

    // Resort: inlined in RPGrpRenderer 0x80254034 (name inferred)
    void setSimpleBlendMode(EBlendMode mode) {
        mBlendMode = mode;
    }

private:
    // Resort offsets follow the base vtable pointer at 0x28 (ctor 0x801B77D8)
    GXColor mColor; // at 0x2C
    f32 mIntensity; // at 0x30
    u32 unk34;
    EBlendMode mBlendMode; // at 0x38
};

} // namespace EGG

#endif
