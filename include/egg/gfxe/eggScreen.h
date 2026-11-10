#ifndef EGG_GFXE_SCREEN_H
#define EGG_GFXE_SCREEN_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggFrustum.h>

#include <nw4r/g3d.h>

#include <revolution/GX.h>

namespace EGG {

class Screen : public Frustum {
public:
    typedef void (*ChangeTVModeFunc)(void* pArg);

    enum TVMode { TV_MODE_STD, TV_MODE_WIDE, TV_MODE_MAX };

    enum FillBufferFlag {
        FILLBUFFER_COLOR = 1 << 0,
        FILLBUFFER_ALPHA = 1 << 1,
        FILLBUFFER_TEXTURE = 1 << 2,
    };

    struct DataEfb {
        struct Viewport {
            f32 x;      // at 0x0
            f32 y;      // at 0x4
            f32 width;  // at 0x8
            f32 height; // at 0xC
            f32 near;   // at 0x10
            f32 far;    // at 0x14
        } vp;

        s32 ox; // at 0x18
        s32 oy; // at 0x1C
    };

public:
    static void Initialize(const u16 maxX[TV_MODE_MAX],
                           const u16 maxY[TV_MODE_MAX],
                           Screen* pUserRoot = NULL);

    Screen();
    Screen(f32 x, f32 y, f32 width, f32 height, const Screen* pParent,
           CanvasMode canvasMode);
    Screen(const Screen& rOther);

    virtual ~Screen() {}                                    // at 0x8
    virtual void SetProjectionGX() const;                   // at 0xC
    virtual void CopyToG3D(nw4r::g3d::Camera camera) const; // at 0x10

    void CopyFromAnother(const Screen& rOther);

    void GetPosSizeInEfb() const;
    const DataEfb& GetDataEfb() const;
    bool IsChangeEfb() const;

    void CalcMatrixForDrawQuad(nw4r::math::MTX34* pMtx, f32 x, f32 y, f32 width,
                               f32 height) const;
    void FillBufferGX(u32 flags, GXColor color, u32 arg2 = 0) const;
    void GetGlobalPos(f32* pX, f32* pY) const;

    const Screen* GetParent() const {
        return mParent;
    }
    void SetParent(const Screen* pParent) {
        mFlags |= FLAG_DIRTY;

        if (spRoot == this) {
            mParent = NULL;
        } else {
            mParent = pParent != NULL ? pParent : spRoot;
        }
    }

    void SetProjectionAbsolute() const {
        mFlags |= FLAG_PROJ_ABSOLUTE;
    }

    // Resort: 0x801B8974 (called by RPGrpView::Calc 0x80255E2C):
    // marks dirty unless already set, then sets FLAG_VPSIZE_ABSOLUTE
    void fn_801B8974();

    // Resort: inline in RPGrpView::Calc 0x80255E2C (sets bit 6 of mFlags)
    void SetUnkFlag6() {
        mFlags |= FLAG_UNK_6;
    }

    const nw4r::math::VEC2& GetPosition() const {
        return mPosition;
    }
    void SetPosition(const nw4r::math::VEC2& rPos) {
        mPosition = rPos;
    }

    static void SetTVMode(TVMode tvMode);
    static void SetTVModeDefault();

    static TVMode GetTVMode() {
        return sTVMode;
    }

    static u16 GetSizeXMax() {
        return sTVModeInfo[sTVMode].width;
    }
    static u16 GetSizeYMax() {
        return sTVModeInfo[sTVMode].height;
    }

    static u16 GetSizeXMax(TVMode tvMode) {
        return sTVModeInfo[tvMode].width;
    }
    static u16 GetSizeYMax(TVMode tvMode) {
        return sTVModeInfo[tvMode].height;
    }

private:
    enum {
        FLAG_ALIGN_EFB_POS = 1 << 1,
        FLAG_ALIGN_EFB_SIZE = 1 << 2,
        FLAG_VPSIZE_ABSOLUTE = 1 << 3,
        FLAG_FORCE_STD_ASPECT = 1 << 5,
        FLAG_UNK_6 = 1 << 6, // Resort
        FLAG_PROJ_ABSOLUTE = 1 << 7,
    };

    struct TVModeRatio {
        TVModeRatio() {}

        f32 widthRatio;  // at 0x0
        f32 heightRatio; // at 0x4
    };

    // Resort: one table of 0xC-byte entries (0x806B4AD8) replaces the
    // separate width/height/ratio arrays (placeholder names)
    struct TVModeInfo {
        u16 width;         // at 0x0
        u16 height;        // at 0x2
        TVModeRatio ratio; // at 0x4
    };

private:
    void Configure();

    void SetViewGX() const;
    void SetViewG3D(nw4r::g3d::Camera camera) const;

    static void CalcRatio();

private:
    const Screen* mParent;      // at 0x3C
    nw4r::math::VEC2 mPosition; // at 0x40
    // Resort: ctor 0x801B83D0 zeroes 0x48..0x54; GetDataEfb 0x801B8E94
    // returns this + 0x58; sRootScreen (0x807CEF30) is 0x88 bytes
    f32 mUnk48;                 // at 0x48
    f32 mUnk4C;                 // at 0x4C
    f32 mUnk50;                 // at 0x50
    f32 mUnk54;                 // at 0x54
    mutable DataEfb mDataEfb;   // at 0x58
    u8 mUnk78[0x88 - 0x78];     // at 0x78

    static TVMode sTVMode;
    static TVModeInfo sTVModeInfo[TV_MODE_MAX];

    static Screen* spRoot;

    static ChangeTVModeFunc sChangeTVModeFunc;
    static void* spChangeTVModeFuncInfo;

    static nw4r::math::VEC2 sCanvasScale;
    static nw4r::math::VEC2 sCanvasOffset;
};

} // namespace EGG

#endif
