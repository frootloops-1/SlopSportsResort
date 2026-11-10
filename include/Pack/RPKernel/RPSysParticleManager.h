#ifndef RP_KERNEL_PARTICLE_MANAGER_H
#define RP_KERNEL_PARTICLE_MANAGER_H
#include <Pack/types_pack.h>

#include <nw4r/ef/ef_particle.h>
#include <nw4r/ef/ef_particlemanager.h>
#include <nw4r/math.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class Unk_806B9908;

/**
 * @brief Particle manager
 * @details Resort: 0xC0 bytes, vtable 0x806B9480, ctor 0x80244070. Resort
 * dropped the Wii Sports life/size/rotate modifiers; the manager instead
 * applies the parameter overrides of its parent emitter's effect
 * (Unk_806B9908, read from emitter+0x154 when the manager is initialized).
 */
class RPSysParticleManager : public nw4r::ef::ParticleManager {
public:
    /**
     * @brief Constructor
     */
    RPSysParticleManager();

    /**
     * @brief Destructor
     */
    virtual ~RPSysParticleManager(); // at 0x20

    /**
     * @brief Prepares this particle manager for creation
     *
     * @param pParent Parent emitter
     * @param pResource Emitter resource data
     * @return Success
     */
    virtual bool Initialize(nw4r::ef::Emitter* pParent,
                            nw4r::ef::EmitterResource* pResource); // at 0x10

    // 0x80243D2C: applies the color/scale/rotate overrides to new particles
    virtual nw4r::ef::Particle*
    CreateParticle(u16 life, nw4r::math::VEC3 pos, nw4r::math::VEC3 vel,
                   const nw4r::math::MTX34* pSpace, f32 momentum,
                   const nw4r::ef::EmitterInheritSetting* pSetting,
                   nw4r::ef::Particle* pReferencePtcl,
                   u16 calcRemain); // at 0x14

    // 0x80243BD4: applies the manager-level overrides before calculating
    virtual void Calc(); // at 0x18

private:
    //! Clears the parameter overrides
    void reset() {
        mpParam = NULL;
    }

    //! Selects the override set: false for the emitter's own particles, true
    //! for child emitters' particles
    BOOL isChildParam() const;

private:
    //! Parameter overrides of the parent emitter's effect
    Unk_806B9908* mpParam; // at 0xBC
};

//! @}

#endif
