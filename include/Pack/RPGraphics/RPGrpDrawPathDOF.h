#ifndef RP_GRAPHICS_DRAW_PATH_DOF_H
#define RP_GRAPHICS_DRAW_PATH_DOF_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpDrawPath.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

// Resort: out-of-line setter on draw path 5 (field at 0x20). Name unproven.
inline void Unk_8024D7D0(EGG::DrawPathBase* pPath, u32 value) {
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(pPath) + 0x20) = value;
}

class RPGrpDrawPathDOF : public RPGrpDrawPath {
public:
    virtual ~RPGrpDrawPathDOF() override {}

    RPGrpDrawPathDOF(EGG::ScnRenderer* pRenderer)
        : RPGrpDrawPath(pRenderer, pRenderer->Unk_8024D7D8()) {
        mpDOF = pRenderer->Unk_8024D7D8();
        Unk_8024D7D0(mpDOF, 0);
    }

private:
    EGG::DrawPathBase* mpDOF; // at 0xC
};

//! @}

#endif
