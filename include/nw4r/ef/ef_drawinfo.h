#ifndef NW4R_EF_DRAW_INFO_H
#define NW4R_EF_DRAW_INFO_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

namespace nw4r {
namespace ef {

// Resort: 0xA0 bytes. Layout from the static instance's __sinit
// (0x80117580) and RPSysEffectMgr's inlined ctor (0x8023D228).
class DrawInfo {
private:
    math::MTX34 mViewMtx; // at 0x0
    math::MTX34 mProjMtx; // at 0x30
    bool mLightEnable;    // at 0x60
    GXLightID mLightMask; // at 0x64
    u32 mUnk68;           // at 0x68 (Resort)
    bool mIsSpotLight;    // at 0x6C
    GXFogType mFogType;   // at 0x70
    f32 mFogStartz;       // at 0x74
    f32 mFogEndz;         // at 0x78
    f32 mFogNearz;        // at 0x7C
    f32 mFogFarz;         // at 0x80
    GXColor mFogColor;    // at 0x84
    f32 mUnk88;           // at 0x88 (Resort)
    math::VEC3 mUnk8C;    // at 0x8C (Resort)
    GXColor mUnk98;       // at 0x98 (Resort)
    GXColor mUnk9C;       // at 0x9C (Resort)

public:
    DrawInfo() {
        math::MTX34Identity(&mViewMtx);
        math::MTX34Identity(&mProjMtx);

        mLightEnable = false;
        mLightMask = GX_LIGHT_NULL;
        mUnk68 = 0;
        mIsSpotLight = true;

        mFogType = GX_FOG_NONE;
        mFogStartz = 0.0f;
        mFogEndz = 1.0f;
        mFogNearz = 0.0f;
        mFogFarz = 1.0f;

        mUnk88 = 0.0f;
        mUnk8C.x = 0.0f;
        mUnk8C.y = 0.0f;
        mUnk8C.z = 0.0f;
        mUnk98.b = 255;
        mUnk98.g = 255;
        mUnk98.r = 255;
        mUnk98.a = 255;
        mUnk9C.b = 0;
        mUnk9C.g = 0;
        mUnk9C.r = 0;
        mUnk9C.a = 255;
    }

    const math::MTX34* GetViewMtx() const {
        return &mViewMtx;
    }
    void SetViewMtx(const math::MTX34& rMtx) {
        mViewMtx = rMtx;
    }

    const math::MTX34* GetProjMtx() const {
        return &mProjMtx;
    }
    void SetProjMtx(const math::MTX34& rMtx) {
        mProjMtx = rMtx;
    }

    bool IsLightEnable() const {
        return mLightEnable;
    }

    GXLightID GetLightMask() const {
        return mLightMask;
    }

    bool IsSpotLight() const {
        return mIsSpotLight;
    }

    void GetFog(GXFogType* pType, f32* pStartZ, f32* pEndZ, f32* pNearZ,
                f32* pFarZ, GXColor* pColor) const {

        *pType = mFogType;
        *pStartZ = mFogStartz;
        *pEndZ = mFogEndz;
        *pNearZ = mFogNearz;
        *pFarZ = mFogFarz;
        *pColor = mFogColor;
    }
};

} // namespace ef
} // namespace nw4r

#endif
