#ifndef RP_KERNEL_EFFECT_MGR_H
#define RP_KERNEL_EFFECT_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/IRPSysHostIOSocket.h>
#include <Pack/RPKernel/RPSysEffectCreator.h>
#include <Pack/RPSingleton.h>

#include <egg/core.h>

//! @addtogroup rp_kernel
//! @{

// Resort: effect color table helpers in unk/sinit_80249EB4 (the unit of the
// Unk_806B98E0 effect class); class and real names unknown, so declared with
// C linkage under their placeholder symbols.
extern "C" {
// Sets the color table's dirty flag (.sbss 0x806F4DA0)
void fn_8024AAF4(BOOL dirty);
// Returns entry `idx` of the 3-entry color table (.bss 0x807CEBCC)
GXColor* fn_8024AAFC(u32 idx);
// Stores `pColor` into entry `idx` and sets the dirty flag if it changed
void fn_8024AB10(const GXColor* pColor, u32 idx);
}

// Forward declarations
class RPSysEffectCreator;

/**
 * @brief Effect manager
 */
class RPSysEffectMgr : public IRPSysHostIOSocket {
public:
    // Resort: 0x8023D80C (no heap argument; RP_SINGLETON_DECL shape without
    // DestroyInstance)
    static void CreateInstance();
    static RPSysEffectMgr* instance() {
        return spInstance;
    }

private:
    RPSysEffectMgr();          // 0x8023C7A4
    virtual ~RPSysEffectMgr(); // at 0x10, 0x8023C6F8

    static RPSysEffectMgr* spInstance;

public:
    /**
     * @brief Effect draw scene ID
     * @details Resort: two creator slots (loops in 0x8023C6F8/0x8023D4DC)
     */
    enum EDrawScene {
        EDrawScene_Scene,  //!< Scene effects
        EDrawScene_Cursor, //!< Cursor/static effects

        EDrawScene_Max
    };

    /**
     * @brief Effect draw group ID
     */
    enum EDrawGroup {
        EDrawGroup_Layer0,
        EDrawGroup_Layer1,
        EDrawGroup_Layer2,
        EDrawGroup_Layer3,

        EDrawGroup_Cursor = 15,
        EDrawGroup_16 = 16,

        EDrawGroup_Max = 64,
    };

    /**
     * @brief Effect update type
     */
    enum ECalcSetting {
        ECalcSetting_All,    //!< Update all effects
        ECalcSetting_Cursor, //!< Only update cursor effects
    };

    /**
     * @brief Effect memory settings
     */
    struct EffectArg {
        //! Heap to use for allocations
        EGG::Heap* pHeap; // at 0x0

        //! Effect object pool size
        int maxEffect; // at 0x4
        //! Emitter object pool size
        int maxEmitter; // at 0x8
        //! Particle manager object pool size
        int maxParticleManager; // at 0xC
        //! Particle object pool size
        int maxParticle; // at 0x10
    };

    /**
     * @brief Framebuffer texture information
     */
    struct EfbTexData {
        //! Texture format (GXTexFmt)
        u8 format; // at 0x0
        //! Texture width
        u16 width; // at 0x2
        //! Texture height
        u16 height; // at 0x4
    };

public:
    // Resort: 0x8023C89C (reads r/g/b from a 0x20-byte EGG::RamStream)
    void fn_8023C89C(u8* pData, GXColor* pOut) const;
    // Resort: 0x8023C900 (projection matrix of the current screen/view)
    nw4r::math::MTX34 fn_8023C900() const;
    // Resort: 0x8023C9D4
    RPSysEffectCreator* fn_8023C9D4(u32 drawScene) const;

    u32 createMemoryManager(EffectArg* pArg); // 0x8023C9E4

    nw4r::ef::Effect* createEffect(const char* pName, u32 drawGroup,
                                   u32 drawScene); // 0x8023D218

    void draw(const nw4r::math::MTX34& rViewMtx, u32 drawGroup,
              u32 drawScene); // 0x8023D228

    void setCaptureEfb(void* pTexture,
                       const EfbTexData& rData); // 0x8023D3B4

    void update(ECalcSetting setting); // 0x8023D3CC
    void fn_8023D454();                // reset

    void stopAllEffect();                            // 0x8023D4DC
    void resetCreator(RPSysEffectCreator* pCreator); // 0x8023D570
    void setCreator(RPSysEffectCreator* pCreator,
                    u32 drawScene); // 0x8023D5AC

    bool fn_8023D5C4(u32 drawGroup) const;
    bool fn_8023D5DC(u32 groupBits, u32 drawGroup) const;
    void fn_8023D604(u32 groupBits, u32 drawGroup);

    void fn_8023D628(u8* pData, u32 idx);
    GXColor* fn_8023D66C(u32 idx);
    void fn_8023D674(const char* pTexName, void* pTexture,
                     const EfbTexData& rData);
    void fn_8023D744(const nw4r::math::VEC3& rPos,
                     const nw4r::math::MTX34& rMtx, f32 far, f32 near);
    void fn_8023D800(s32 arg0, u32 arg1);

private:
    //! Scene effect creators
    RPSysEffectCreator* mpEffectCreators[EDrawScene_Max]; // at 0x4
    //! Freed by the destructor
    void* mUnkC; // at 0xC

public:
    bool mUnk10; // at 0x10
    bool mUnk11; // at 0x11
    s32 mUnk14;  // at 0x14
    u32 mUnk18;  // at 0x18

private:
    //! Per draw group bitmask of active group bits (bit = groupBits >> 4)
    EGG::TBitFlag<u32> mUnk1C[16]; // at 0x1C
};

//! @}

#endif
