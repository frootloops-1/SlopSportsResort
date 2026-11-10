#ifndef RP_GRAPHICS_DRAW_PATH_HDR_H
#define RP_GRAPHICS_DRAW_PATH_HDR_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpDrawPath.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

class RPGrpDrawPathHDR : public RPGrpDrawPath {
public:
    virtual ~RPGrpDrawPathHDR() override {}

    RPGrpDrawPathHDR(EGG::ScnRenderer* pRenderer)
        : RPGrpDrawPath(pRenderer, pRenderer->Unk_8024D74C()) {}
};

//! @}

#endif
