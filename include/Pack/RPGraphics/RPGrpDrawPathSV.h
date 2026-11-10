#ifndef RP_GRAPHICS_DRAW_PATH_SV_H
#define RP_GRAPHICS_DRAW_PATH_SV_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpDrawPath.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

// Resort: one class for draw paths 1 and 2 (bool selects path 2).
class RPGrpDrawPathSV : public RPGrpDrawPath {
    friend class RPGrpDrawPathManager;

public:
    virtual ~RPGrpDrawPathSV() override {}

    RPGrpDrawPathSV(EGG::ScnRenderer* pRenderer, bool second)
        : RPGrpDrawPath(pRenderer, second ? pRenderer->Unk_8024D6DC()
                                          : pRenderer->Unk_8024D6D0()) {
        mpSV = second ? pRenderer->Unk_8024D6DC() : pRenderer->Unk_8024D6D0();
    }

private:
    EGG::DrawPathBase* mpSV; // at 0xC
};

//! @}

#endif
