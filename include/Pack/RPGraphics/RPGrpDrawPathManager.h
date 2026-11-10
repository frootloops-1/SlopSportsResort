#ifndef RP_GRAPHICS_DRAW_PATH_MANAGER_H
#define RP_GRAPHICS_DRAW_PATH_MANAGER_H
#include <Pack/types_pack.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpDrawPathBloom;
class RPGrpDrawPathDOF;
class RPGrpDrawPathHDR;
class RPGrpDrawPathLightMap;
class RPGrpDrawPathShadowTexture;
class RPGrpDrawPathSV;
class RPGrpDrawPathXluSnap;
class RPGrpDrawPath;
class RPGrpModelScene;

/**
 * @brief Draw path manager
 */
class RPGrpDrawPathManager : public EGG::IScnProc {
public:
    /**
     * @brief Flags to enable draw path types with Construct
     */
    enum {
        EFlag_DrawPathLightMap = 1 << 0,
        EFlag_DrawPathShadowTexture = 1 << 1,
        EFlag_DrawPathXluSnap = 1 << 2,
        EFlag_DrawPathSV = 1 << 3,
        EFlag_DrawPathSV2 = 1 << 4, // Resort: RPGrpDrawPathSV on path 2
        EFlag_DrawPathHDR = 1 << 5,
        EFlag_DrawPathBloom = 1 << 6,
        EFlag_DrawPathDOF = 1 << 7,
    };

    /**
     * @brief Draw path slots
     */
    enum {
        EDrawPath_LightMap,
        EDrawPath_ShadowTexture,
        EDrawPath_XluSnap,
        EDrawPath_SV,
        EDrawPath_Unk4,
        EDrawPath_HDR,
        EDrawPath_Bloom,
        EDrawPath_DOF,

        EDrawPath_Max
    };

public:
    static RPGrpDrawPathManager* Construct(u32 pathFlags,
                                           RPGrpModelScene* pModelScene);

    virtual void scnProcDraw(u16 idx) override; // at 0x8

    virtual ~RPGrpDrawPathManager() override {} // at 0xC

    void Unk_8024D360();

    // TODO: unk14 is the external draw callback (an EGG::IScnProc-like object)
    void SetUnk14(void* pProc) {
        unk14 = reinterpret_cast<u32>(pProc);
    }

    RPGrpDrawPathLightMap* GetDrawPathLightMap() const {
        return reinterpret_cast<RPGrpDrawPathLightMap*>(
            mpDrawPaths[EDrawPath_LightMap]);
    }

private:
    RPGrpDrawPathManager(u32 pathFlags, RPGrpModelScene* pModelScene);

private:
    u16 unkC;                      // at 0xC
    RPGrpModelScene* mpModelScene; // at 0x10
    u32 unk14;                     // at 0x14
    RPGrpDrawPath* mpDrawPaths[EDrawPath_Max]; // at 0x18
};

//! @}

#endif
