#ifndef EGG_GFXE_POST_EFFECT_MASK_DOF_H
#define EGG_GFXE_POST_EFFECT_MASK_DOF_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggPostEffectBase.h>
#include <egg/prim.h>

#include <revolution/GX.h>

namespace EGG {

// Forward declarations
class CpuTexture;
class PostEffectMaskDOF;

// Name unknown: rebuilds the 256x4 depth gradation texture (at 0x30)
extern "C" void fn_8009EF30(PostEffectMaskDOF* pSelf);

class PostEffectMaskDOF : public PostEffectBase {
    friend void fn_8009EF30(PostEffectMaskDOF* pSelf);

public:
    enum {
        cFlag_UpdateDepthTex = 1 << 2,
        cFlag_RoundOffset = 1 << 3,
    };

public:
    PostEffectMaskDOF();
    virtual ~PostEffectMaskDOF() {} // at 0x8

    virtual void draw(f32 w, f32 h);    // at 0x10
    virtual void reset();               // at 0x14
    virtual void setMaterialInternal(); // at 0x18

    void setUpGradation();

    void setMode(s32 mode) {
        mMode = mode;
    }

    void setStart(f32 start) {
#line 69
        EGG_ASSERT(start >= 0.f && start <= 1.f);
        mNear = start;
    }
    void setEnd(f32 end) {
#line 71
        EGG_ASSERT(end >= 0.f && end <= 1.f);
        mFar = end;
    }
    void setCenter(f32 center) {
#line 73
        EGG_ASSERT(center >= 0.f && center <= 1.f);
        mFocus = center;
    }

    static const GXColor& getCenterColor();
    static const GXColor& getFarColor();
    static const GXColor& getNearColor();

private:
    u8 mDofFlags;               // at 0x20
    u32 unk24;                  // at 0x24
    CpuTexture* mpMaskTexture;  // at 0x28
    u32 unk2C;                  // at 0x2C
    CpuTexture* mpDepthTexture; // at 0x30
    f32 mFocus;                 // at 0x34
    f32 mNear;                  // at 0x38
    f32 mFar;                   // at 0x3C
    f32 mTexOffsetS;            // at 0x40
    f32 mTexOffsetT;            // at 0x44
    f32 unk48;                  // at 0x48
    s32 mMode;                  // at 0x4C
};

} // namespace EGG

#endif
