#ifndef RP_GRAPHICS_MODEL_MANAGER_H
#define RP_GRAPHICS_MODEL_MANAGER_H
#include <Pack/types_pack.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpDrawPathManager;
class RPGrpFogManager;
class RPGrpLightManager;
class RPGrpModelMisc;
class RPGrpModelResManager;
class RPGrpModelScene;
namespace EGG {
class Allocator;
class LightManager;
} // namespace EGG

/**
 * @brief Model manager
 */
class RPGrpModelManager {
public:
    //! Maximum number of model scenes
    static const int MAX_SCENE = 8;

public:
    /**
     * @brief Gets the currently active manager instance
     */
    static RPGrpModelManager* GetCurrent() {
        return spCurrent;
    }

    RPGrpModelManager(EGG::Allocator* pAllocator,
                      EGG::Allocator* pSceneAllocator);

    EGG::LightManager* GetLightManager(u8 drawScene) const;
    RPGrpFogManager* GetFogManager(u8 drawScene) const; // name inferred
    RPGrpDrawPathManager* GetDrawPathManager(u8 drawScene) const;

    // Resort: out of line (0x801D1E90, u8 index; called from
    // RPGrpViewRender3D 0x802562A8 and RPGrpRenderer 0x80253D8C)
    RPGrpModelScene* GetModelScene(u8 drawScene);

    void SetUnk50(bool value) {
        unk50 = value;
    }

    // TODO: names unknown (placeholders for fn_XXXX symbols)
    static void fn_801ADEB0();
    void fn_801ADEC8();
    void fn_801ADF18();
    void fn_801ADF78();
    void fn_801ADFD0();
    void fn_801AE070();
    void fn_801AE160();
    void fn_801AE1B4(u8 drawScene, u32 arg1, u8 viewNum,
                     RPGrpLightManager* pLightManager,
                     RPGrpFogManager* pFogManager);
    void fn_801AE21C();

private:
    //! Allocator used for model-related allocations
    static RPGrpModelManager* spCurrent;

    // Resort layout (ctor 0x802528B8): size 0x60, vptr at 0x5C, no ModelMisc

    //! Model scenes
    RPGrpModelScene* mpModelScenes[MAX_SCENE]; // at 0x0
    void* unk20[MAX_SCENE];                    // at 0x20
    u8 unk40;                                  // at 0x40 (count over unk20)
    //! Resource manager
    RPGrpModelResManager* mpResManager; // at 0x44
    //! Model allocator
    EGG::Allocator* mpAllocator; // at 0x48
    //! Scene allocator (inferred)
    EGG::Allocator* mpSceneAllocator; // at 0x4C
    bool unk50;                       // at 0x50 (PostCalculate skip flag)
    u8* unk54;                        // at 0x54 (new u8[4])
    u8* unk58;                        // at 0x58 (new u8[4])

public:
    virtual ~RPGrpModelManager() {} // at 0x8
};

//! @}

#endif
