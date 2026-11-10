#ifndef RP_GRAPHICS_DRAW_PATH_XLU_SNAP_H
#define RP_GRAPHICS_DRAW_PATH_XLU_SNAP_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpDrawPath.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

class RPGrpDrawPathXluSnap : public RPGrpDrawPath {
public:
    virtual ~RPGrpDrawPathXluSnap() override {}

    RPGrpDrawPathXluSnap(EGG::ScnRenderer* pRenderer)
        : RPGrpDrawPath(pRenderer, pRenderer->Unk_8024D8D0()) {
        mpXluSnap = pRenderer->Unk_8024D8D0();
    }

private:
    EGG::DrawPathBase* mpXluSnap; // at 0xC
};

//! @}

#endif
