#ifndef EGG_CORE_VIDEO_H
#define EGG_CORE_VIDEO_H
#include <egg/types_egg.h>

#include <egg/prim.h>

#include <revolution/GX.h>
#include <revolution/VI.h>

namespace EGG {

class Video {
public:
    //! Resort: table of 10 render modes that getStandardRenderModeObj picks
    //! from (default instance lbl_80662A28, used by configure 0x801C7654 when
    //! the table argument is NULL). Real name unknown.
    struct Unk_80662A28 {
        GXRenderModeObj* mObjs[10]; // at 0x0
    };

public:
    explicit Video(GXRenderModeObj* pRenderMode)
        : mRenderMode(NULL), mConfiguredTime(0) {

        initialize(pRenderMode, NULL);
    }

    // Resort: initialize/configure take the render mode table as a second
    // argument (0x801C7600 forwards r5 to configure)
    void initialize(GXRenderModeObj* pRenderMode,
                    const Unk_80662A28* pModeTable);
    GXRenderModeObj* configure(GXRenderModeObj* pRenderMode,
                               const Unk_80662A28* pModeTable);

    static u32 getTickPerVRetrace(u32 tvFormat);
    static u32 getTickPerVRetrace();

    static const GXRenderModeObj*
    getStandardRenderModeObj(const Unk_80662A28* pModeTable);

    bool isBlack() {
        return mFlags.offBit(BIT_VIDEO_SHOW);
    }
    void changeBlack() {
        VISetBlack(mFlags.offBit(BIT_VIDEO_SHOW));
        mFlags.toggleBit(BIT_VIDEO_SHOW);
    }

    GXRenderModeObj* getRenderModeObj() {
        return mRenderMode;
    }

    u16 getFbWidth() {
        return mRenderMode->fbWidth;
    }
    u16 getEfbHeight() {
        return mRenderMode->efbHeight;
    }

private:
    enum {
        BIT_VIDEO_SHOW,
    };

private:
    GXRenderModeObj* mRenderMode; // at 0x0
    TBitFlag<u8> mFlags;          // at 0x4
    s32 mConfiguredTime;          // at 0x8
};

} // namespace EGG

#endif
