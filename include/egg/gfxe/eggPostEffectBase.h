#ifndef EGG_GFXE_POST_EFFECT_BASE_H
#define EGG_GFXE_POST_EFFECT_BASE_H
#include <egg/types_egg.h>

#include <egg/prim.h>

#include <revolution/GX.h>

namespace EGG {

// Forward declarations
class CapTexture;

class PostEffectBase {
public:
    enum BlendMode {
        cBlendMode_None,
        cBlendMode_Normal,
        cBlendMode_Add,
        cBlendMode_MulAdd,
        cBlendMode_4,
        cBlendMode_5,
        cBlendMode_AddAlpha,
        cBlendMode_7,
        cBlendMode_8,
        cBlendMode_Mul,
    };

protected:
    // Resort layout (ctor 0x801B5540, draw 0x801B559C, loadTextureInternal
    // 0x801B5728): the vtable is at 0x28, unlike Wii Sports
    BlendMode mBlendMode;      // at 0x0
    CapTexture* mpCapTexture;  // at 0x4
    GXTexMapID mCapTexMap;     // at 0x8
    CapTexture* mpCapTexture2; // at 0xC
    GXTexMapID mCapTexMap2;    // at 0x10
    f32 mOffsetX;              // at 0x14
    f32 mOffsetY;              // at 0x18
    f32 mScaleX;               // at 0x1C
    f32 mScaleY;               // at 0x20
    f32 mUnk24;                // at 0x24

public:
    // Resort: 0x801B5540
    PostEffectBase();
    virtual ~PostEffectBase() {} // at 0x8

    // Resort vtable (0x806B49C4): no configure/reset slots
    virtual void draw(f32 w, f32 h);                             // at 0xC
    virtual void setMaterialInternal();                          // at 0x10
    virtual void loadTextureInternal();                          // at 0x14
    virtual void drawScreenInternal(f32 x, f32 y, f32 w, f32 h); // at 0x18

    static void setProjection(const Screen& rScreen);
    void drawTexture();

    void setBlendMode(BlendMode mode) {
        mBlendMode = mode;
    }

    CapTexture* getCapTexture() const {
        return mpCapTexture;
    }
    void setCapTexture(CapTexture* pCapTexture) {
        mpCapTexture = pCapTexture;
    }

protected:
    void setVtxState();
    void setMatColorChannel();
    void setMatInd();
    void setMatPE();
    void setBlendModeInternal();

    static void scaleRGBA(GXColor* pOut, const GXColor& rIn, f32 scale,
                          bool clamp);

};

} // namespace EGG

#endif
