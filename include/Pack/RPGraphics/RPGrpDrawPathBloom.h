#ifndef RP_GRAPHICS_DRAW_PATH_BLOOM_H
#define RP_GRAPHICS_DRAW_PATH_BLOOM_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpDrawPath.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

class RPGrpDrawPathBloom : public RPGrpDrawPath {
public:
    virtual ~RPGrpDrawPathBloom() override {}

    RPGrpDrawPathBloom(EGG::ScnRenderer* pRenderer)
        : RPGrpDrawPath(pRenderer, pRenderer->Unk_8024D854()) {
        mpBloom = pRenderer->Unk_8024D854();
    }

private:
    char unkC[0x10 - 0xC];
    EGG::DrawPathBase* mpBloom; // at 0x10
    char unk14[0x34 - 0x14];    // original allocates 0x34 bytes
};

//! @}

#endif
