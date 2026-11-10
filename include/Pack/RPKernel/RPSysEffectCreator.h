#ifndef RP_KERNEL_EFFECT_CREATOR_H
#define RP_KERNEL_EFFECT_CREATOR_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/RPSysEffectMemoryManager.h>

#include <egg/core.h>

#include <nw4r/ef.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Effect creator
 */
class RPSysEffectCreator : public EGG::Disposer {
public:
    //! Number of effect/texture project slots (Resort: 8, ctor 0x8023F748)
    static const int RESOURCE_MAX = 8;

    /**
     * @brief Constructor
     *
     * @param drawScene Effect draw scene
     */
    explicit RPSysEffectCreator(u32 drawScene);

    /**
     * @brief Destructor
     */
    virtual ~RPSysEffectCreator(); // at 0x8

    // Resort: 0x8023F964
    void createSlowSystem();
    // Resort: 0x8023F934
    void setFrameRate(f32 frameRate);
    // Resort: 0x8023F924
    bool isSlowSystem() const;
    // Resort: 0x8023F8A0 (attaches a .breff/.breft pair to slot `idx`)
    bool fn_8023F8A0(void* pEffectProject, void* pTextureProject, int idx);
    // Resort: 0x8023F800 (releases every attached resource slot)
    void fn_8023F800();
    // Resort: 0x8023F640
    void stopAllEffect();
    // Resort: 0x8023F580
    nw4r::ef::Effect* createEffect(const char* pName, u32 drawGroup);
    // Resort: 0x8023F56C (forwards the process camera to the slow system)
    void fn_8023F56C(const nw4r::math::VEC3& rPos,
                     const nw4r::math::MTX34& rMtx, f32 far, f32 near);
    // Resort: 0x8023F52C (calcs the main system, then update())
    void fn_8023F52C();
    // Resort: 0x8023F2C0 (draws both systems, optionally Z-sorted)
    void fn_8023F2C0(const nw4r::ef::DrawInfo& rDrawInfo, u32 drawGroup,
                     u32 drawScene, bool sort);
    // Resort: 0x8023F2B0
    nw4r::ef::TextureProject* fn_8023F2B0(int idx) const;
    // Resort: 0x8023F248 (user flags -> draw group bits)
    u32 fn_8023F248(u16 flags) const;
    // Resort: 0x8023F154 (calcs this creator's groups of pSystem)
    void fn_8023F154(nw4r::ef::EffectSystem* pSystem);
    // Resort: 0x8023EB18
    void update();

private:
    /**
     * @brief Save buffer index
     */
    enum ESaveBuffer {
        ESaveBuffer_1st, //!< First of the two alternating buffers
        ESaveBuffer_2nd, //!< Second of the two alternating buffers

        ESaveBuffer_Max
    };

    //! Slow system effect object pool size
    static const u16 SLOW_MAX_EFFECT = 50;
    //! Slow system emitter object pool size
    static const u16 SLOW_MAX_EMITTER = 100;
    //! Slow system particle manager object pool size
    static const u16 SLOW_MAX_PARTICLE_MANAGER = 150;
    //! Slow system particle object pool size
    static const u16 SLOW_MAX_PARTICLE = 500;

private:
    //! Group ID prefix inherited by child effects
    u32 mBaseGroupID; // at 0x10

    //! Effect data projects (.BREFF)
    nw4r::ef::EffectProject* mpEffectProject[RESOURCE_MAX]; // at 0x14
    //! Effect texture projects (.BREFT)
    nw4r::ef::TextureProject* mpTextureProject[RESOURCE_MAX]; // at 0x34

    //! Parameter save buffer where slow system data will be saved
    u32 mBackSaveBuffer; // at 0x54
    //! Whether slow-motion effects are about to be processed
    BOOL mIsSlowEffect; // at 0x58

    //! Current frame processing position
    f32 mFrame; // at 0x5C
    //! Frame processing rate
    f32 mFrameRate; // at 0x60

    //! Effect system for slow-motion effects (Resort: no separate memory
    //! manager member; update() reads it from this system)
    nw4r::ef::EffectSystem* mpSlowSystem; // at 0x64

    //! Emitter parameter save buffers
    nw4r::ef::EmitterParameter* mpEmitterParamSave[ESaveBuffer_Max]; // at 0x68
    //! Particle parameter save buffers
    nw4r::ef::ParticleParameter*
        mpParticleParamSave[ESaveBuffer_Max]; // at 0x70
};

//! @}

#endif
