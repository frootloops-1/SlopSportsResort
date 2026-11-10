#ifndef RP_SPORTS_MENU_BG_MODEL_H
#define RP_SPORTS_MENU_BG_MODEL_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/RP_DEBUG_STUB_1.h>

#include <nw4r/math.h>

// Forward declarations
class RPGrpCamera;
class RPGrpModel;
namespace EGG {
class Archive;
}

/**
 * @brief Menu background model (menu_BG_model in the common archive)
 */
class RPSportsMenuBgModel : public RP_DEBUG_STUB_1 {
public:
    RPSportsMenuBgModel(u8 viewNo, u8 drawScene, u8 anmFrame);
    virtual ~RPSportsMenuBgModel(); // at 0x8

    void Load(EGG::Archive* pArchive);
    void Reset();
    void Calc();

private:
    u8 mViewNo;                   // at 0x4
    u8 mDrawScene;                // at 0x5
    u8 mAnmFrame;                 // at 0x6
    RPGrpModel* mpModel;          // at 0x8
    RPGrpCamera* mpCamera;        // at 0xC
    nw4r::math::VEC3 mPosition;   // at 0x10
    nw4r::math::VEC3 mScale;      // at 0x1C
};

#endif
