#ifndef EGG_GFXE_SHADOW_TEXTURE_H
#define EGG_GFXE_SHADOW_TEXTURE_H
#include "eggModelSnapshot.h"
#include "eggPostEffectBase.h"
#include "types_egg.h"

#include <nw4r/g3d.h>
#include <nw4r/math.h>

namespace EGG {

// Forward declarations
class Screen;

class ShadowTexture : public ModelSnapshot {
public:
    // Inferred from SetMaterial: each value selects a DrawGX blend mode
    enum Blend {
        BLEND_0, // DrawGX::BLEND_MUL
        BLEND_1, // DrawGX::BLEND_SUB
        BLEND_2, // DrawGX::BLEND_NORMAL
    };

    static const u32 EFFECT_MTX_MAX = 32;

    struct BlurParam {
        f32 radius; // at 0x0
        u8 alpha;   // at 0x4
    };

    struct EffectMtxSet {
        nw4r::g3d::ResTexSrt m_texSrt; // at 0x0
        u8 m_texCoordID;               // at 0x4
    };

public:
    ShadowTexture(u16 size, u16 format, u16 mdlMax);
    virtual ~ShadowTexture(); // at 0x8

    virtual void InitList(); // at 0x18 (overrides ModelSnapshot::InitList)

    void Replace(ModelEx* pModelEx, const char* pName, bool arg2 = false);

    void Calc();
    void CalcShadow();
    void CalcProjectionMatrix();

    void DrawShape();
    void Draw(Screen* pScreen, bool arg1, bool clear, bool restoreClearColor);

    static void BeginDrawQuad(Blend blend);
    void DrawQuad(const nw4r::math::MTX34& rMtx, const GXColor& rColor) const;
    void SetUpTextureAndColor(const nw4r::math::MTX34& rMtx,
                              const GXColor& rColor) const;
    static void SetMaterial(Blend blend);

    // Temporary names, needed for regalloc
    void SetCapTexture0(CapTexture* pCapTexture) {
        POST_EFF_0xE4->setCapTexture(pCapTexture);
    }
    void SetCapTexture1(CapTexture* pCapTexture) {
        POST_EFF_0xE8->setCapTexture(pCapTexture);
    }

    static u16 sFlags;

    // private:
    u16 SHORT_0x70;                              // at 0x70
    u8 mAlpha;                                   // at 0x72
    f32 mAdjust;                                 // at 0x74
    nw4r::math::VEC3 mLightDir;                  // at 0x78
    nw4r::math::MTX34 mViewMtx;                  // at 0x84
    nw4r::math::MTX34 mProjMtx;                  // at 0xB4
    PostEffectBase* POST_EFF_0xE4;               // at 0xE4 (PostEffectBlur)
    PostEffectBase* POST_EFF_0xE8;               // at 0xE8 (PostEffectBlurSimple)
    BlurParam mBlurParam[2];                     // at 0xEC
    u8 m_effectMtxNum;                           // at 0xFC
    EffectMtxSet m_effectMtxSet[EFFECT_MTX_MAX]; // at 0x100
};

} // namespace EGG

#endif
