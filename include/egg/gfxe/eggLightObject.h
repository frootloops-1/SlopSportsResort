#ifndef EGG_GFXE_LIGHT_OBJECT_H
#define EGG_GFXE_LIGHT_OBJECT_H
#include <egg/types_egg.h>

#include <egg/core.h>
#include <egg/math.h>
#include <egg/prim/eggAssert.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

namespace nw4r {
namespace g3d {
class LightObj;
class ResAnmLight;
} // namespace g3d
} // namespace nw4r

namespace EGG {

class LightObject : public IBinary<LightObject> {
    friend class LightManager;

public:
    struct BinData {
        u8 spotFn;             // at 0x10
        u8 distAttnFn;         // at 0x11
        u8 coordType;          // at 0x12
        u8 lightType;          // at 0x13
        u16 index;             // at 0x14
        u16 flags;             // at 0x16
        nw4r::math::_VEC3 pos; // at 0x18
        nw4r::math::_VEC3 at;  // at 0x24
        f32 intensity;         // at 0x30
        GXColor color;         // at 0x34
        GXColor ambColor;      // at 0x38
        f32 cutoff;            // at 0x3C
        f32 refDist;           // at 0x40
        f32 refBrightness;     // at 0x44
        char UNK_0x48[0x8];
    };

    enum LightType {
        cLightType_Point,
        cLightType_Dir,
        cLightType_Spot,

        cLightType_Max
    };

    // Values of field_0x34 (inferred from CalcView; names unknown)
    enum CoordType {
        cCoordType_0, // world space, transformed by the view matrix
        cCoordType_1, // as 0, but the direction becomes a half-angle vector
        cCoordType_2, // already in view space (copied as-is)
        cCoordType_3, // fixed: at (0,0,-dist), dir (0,0,-1)
        cCoordType_4, // fixed: pos (0,0,dist), dir (0,0,1)
        cCoordType_5,
    };

public:
    LightObject();

    virtual void SetBinaryInner(const Bin& rBin); // at 0x8
    virtual void GetBinaryInner(Bin* pBin) const; // at 0xC
    virtual const char* GetBinaryType() const;    // at 0x10
    virtual u32 GetBinarySize() const;            // at 0x14
    virtual u8 GetVersion() const;                // at 0x18

    void Reset();
    void Calc();
    void CalcView(const nw4r::math::MTX34& rViewMtx);

    void CalcFinalDirColor(const LightTexture& rTexture, nw4r::math::VEC3* pDir,
                           GXColor* pColor) const;

    void InitGX(GXLightObj* pObj) const;
    void CopyToG3D_World(nw4r::g3d::LightObj& rObj) const;
    void CopyToG3D_View(nw4r::g3d::LightObj& rObj,
                        const nw4r::math::MTX34& rViewMtx) const;
    void CopyFromG3D(const nw4r::g3d::ResAnmLight& rAnm, f32 frame);

    void CalcDirDist();
    void CalcAt();

    void SetPos(const nw4r::math::VEC3& rPos) {
        mPos = rPos;
        CalcDirDist();
    }
    void SetAt(const nw4r::math::VEC3& rAt) {
        mAt = rAt;
        CalcDirDist();
    }
    void SetPosAt(const nw4r::math::VEC3& rPos, const nw4r::math::VEC3& rAt) {
        mPos = rPos;
        mAt = rAt;
        CalcDirDist();
    }

    u16 GetIndex() const {
        return mIndex;
    }
    f32 GetDist() const {
        return mDist;
    }
    u16 getFlags() const {
        return mFlags;
    }

    void SetDir(const nw4r::math::VEC3& dir) {
#line 559
        EGG_ASSERT(VEC3Len( &dir ) > 0.f);
        mDir = dir;
        CalcAt();
    }

private:
    enum {
        cFlag_Enable = 1 << 0,
        cFlag_5 = 1 << 5,
        cFlag_6 = 1 << 6,
        cFlag_UseAttnA = 1 << 7,
        cFlag_UseAttnK = 1 << 8,
        cFlag_ColorEnable = 1 << 9,
        cFlag_AlphaEnable = 1 << 10,
        cFlag_Specular = 1 << 11,
    };

    static const u8 VERSION = 1;

private:
    u16 mIndex;                // at 0x4
    u16 field_0x06;            // at 0x6
    nw4r::math::VEC3 mAt;      // at 0x8
    nw4r::math::VEC3 mPos;     // at 0x14
    nw4r::math::VEC3 mDir;     // at 0x20
    GXColor mColor;            // at 0x2C
    f32 mIntensity;            // at 0x30
    CoordType field_0x34;      // at 0x34
    f32 mDist;                 // at 0x38
    GXColor mAmbColor;         // at 0x3C
    LightType mLightType;      // at 0x40
    f32 mCutoff;               // at 0x44
    f32 mRefDist;              // at 0x48
    f32 mRefBrightness;        // at 0x4C
    nw4r::math::VEC3 mAttnA;   // at 0x50
    nw4r::math::VEC3 mAttnK;   // at 0x5C
    GXSpotFn mSpotFn;          // at 0x68
    GXDistAttnFn mDistAttnFn;  // at 0x6C
    f32 mShininess;            // at 0x70
    u16 field_0x74;            // at 0x74
    u16 mFlags;                // at 0x76
    u32 field_0x78;            // at 0x78
    nw4r::math::VEC3 mWorkDir; // at 0x7C
    GXColor mLightColor;       // at 0x88
    nw4r::math::VEC3 mViewPos; // at 0x8C
    nw4r::math::VEC3 mViewAt;  // at 0x98
    nw4r::math::VEC3 mViewDir; // at 0xA4
};

} // namespace EGG

#endif
