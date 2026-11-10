#ifndef RP_GRAPHICS_MODEL_SCENE_H
#define RP_GRAPHICS_MODEL_SCENE_H
#include <Pack/types_pack.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpCamera;
class RPGrpDrawPathManager;
class RPGrpFogManager;
class RPGrpLightManager;
class RPGrpModel;
class RPGrpProjectionObject;
class RPGrpScreen;
namespace nw4r {
namespace g3d {
class ScnRoot;
} // namespace g3d
} // namespace nw4r
namespace EGG {
class Allocator;
class ScnRenderer;
} // namespace EGG

/**
 * @brief Model rendering scene
 */
class RPGrpModelScene {
    //! Only the model manager can change the current allocator
    friend class RPGrpModelManager;

private:
    //! Draw ("entry") list of models
    struct EntryList {
        RPGrpModel* pHead; // at 0x0
        RPGrpModel* pTail; // at 0x4
    };

private:
    // Resort layout (ctor 0x802569BC; vptr at 0xA8). The ogws priority
    // tables at 0x4/0x8 are gone, so the managers moved up by 8 bytes.
    u8 mViewNum;                             // at 0x0 (ctor 3rd param)
    u8 unk1;                                 // at 0x1
    u8 unk2;                                 // at 0x2
    u8 mFlags;                               // at 0x3 (ctor stores 7)
    u32 unk4;                                // at 0x4
    RPGrpLightManager* mpLightManager;       // at 0x8
    RPGrpFogManager* mpFogManager;           // at 0xC
    RPGrpDrawPathManager* mpDrawPathManager; // at 0x10
    RPGrpProjectionObject* mpProjectionObjects[32]; // at 0x14
    u32 unk94;                               // at 0x94
    nw4r::g3d::ScnRoot* mpScnRoot;           // at 0x98
    EGG::ScnRenderer* mpScnRootEx;           // at 0x9C
    u32 unkA0;                               // at 0xA0
    u32 unkA4;                               // at 0xA4

public:
    RPGrpModelScene(u32 arg0, u8 viewNum, RPGrpLightManager* pLightManager,
                    RPGrpFogManager* pFogManager);

    // Resort: the vtable (0x806B9F30) holds only the dtor (fn_80256944);
    // the other ogws virtuals are called directly (RPGrpViewRender3D).
    virtual ~RPGrpModelScene(); // at 0x8
    void CalcView();
    void CalcDrawList();
    void Draw();                             // Resort: 0x802565DC
    void DrawFinish();
    void PreConditionForRenderingGX() const; // Resort: 0x80256434
    void fn_801B1A14(RPGrpModel* pModel);

    // Resort: 0x8025677C, if (mFlags & 1) mpScnRootEx->CalcView()
    // (split out of DrawPrepare; RPGrpViewRender3D::PrepareDraw 0x802562A8)
    void fn_8025677C();

    // Resort: GetDrawPathManager (0x80252400) reads this after GetModelScene
    RPGrpDrawPathManager* GetDrawPathManager() const {
        return mpDrawPathManager;
    }

    // TODO: names unknown (placeholders for fn_XXXX symbols)
    void fn_801B19F0(RPGrpModel* pModel);
    void fn_801B1A94(RPGrpProjectionObject* pProjObj);
    void fn_801B1AAC(RPGrpProjectionObject* pProjObj);
    void fn_801B1C44();
    void fn_801B1DBC();
    static void fn_801B23E0();

public:
    // Resort: 0x80256794, no longer calls CalcView
    void DrawPrepare(const RPGrpCamera* pCamera, const RPGrpScreen* pScreen);

private:
    //! Allocator used for scene allocations (inferred name)
    static EGG::Allocator* spAllocator;
};

//! @}

#endif
