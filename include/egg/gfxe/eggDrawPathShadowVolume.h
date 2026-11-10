#ifndef EGG_GFXE_DRAW_PATH_SHADOW_VOLUME_H
#define EGG_GFXE_DRAW_PATH_SHADOW_VOLUME_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggDrawPathBase.h>

namespace EGG {

class DrawPathShadowVolume : public DrawPathBase {
    friend class ScnRenderer;

public:
    DrawPathShadowVolume();
    virtual ~DrawPathShadowVolume(); // at 0x8
    virtual u16 getNumStep() const;  // at 0x1C
    virtual void internalCalc();     // at 0x24
    virtual void internalDraw(u16);  // at 0x28

private:
    enum Step {
        cStep_0,
        cStep_1,
        cStep_2,

        cStep_Max
    };

private:
    char UNK_0x7A[0x7C - 0x7A];
    u16 mFlags;               // at 0x7C
    u8 mClearAlpha;           // at 0x7E
    TextureBuffer* mpFull;    // at 0x80
    TextureBuffer* mpZBuffer; // at 0x84
    GXColor mColor;           // at 0x88
    int mBlendType;           // at 0x8C
    u32 mDrawFlag;            // at 0x90
    s16 mFogIndex;            // at 0x94
};

} // namespace EGG

#endif
