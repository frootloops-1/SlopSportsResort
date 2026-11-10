#ifndef EGG_GFXE_DRAW_PATH_XLU_SNAP_H
#define EGG_GFXE_DRAW_PATH_XLU_SNAP_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggDrawPathBase.h>

namespace EGG {

class DrawPathXluSnap : public DrawPathBase {
    friend class ScnRenderer;

public:
    DrawPathXluSnap();
    virtual ~DrawPathXluSnap();     // at 0x8
    virtual u16 getNumStep() const; // at 0x1C
    virtual void internalCalc();    // at 0x24
    virtual void internalDraw(u16); // at 0x28

private:
    enum Step {
        cStep_0,
        cStep_1,
        cStep_2,
        cStep_3,

        cStep_Max
    };

private:
    char UNK_0x7A[0x7C - 0x7A];
    u8 mFlags;                // at 0x7C
    u8 mAlpha;                // at 0x7D
    int mMode;                // at 0x80
    TextureBuffer* mpXluBuf;  // at 0x84
    TextureBuffer* mpZBuf;    // at 0x88
    TextureBuffer* mpOpaBuf;  // at 0x8C
};

} // namespace EGG

#endif
