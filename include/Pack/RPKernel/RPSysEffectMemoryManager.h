#ifndef RP_KERNEL_EFFECT_MEMORY_MANAGER_H
#define RP_KERNEL_EFFECT_MEMORY_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/RPSysEffectBase.h>
#include <Pack/RPKernel/RPSysParticleManager.h>

#include <nw4r/ef/ef_emitter.h>

/**
 * @brief Emitter object type pooled by RPSysEffectMemoryManager (Resort only)
 * @details Resort: 0x158 bytes, vtable 0x806B94B8, ctor 0x80244ABC,
 * dtor 0x80244A6C (unit unk/text_802440B4). One extra instance is created
 * by RPSysEffectMgr/RPSysEffectCreator for EffectSystem+0xC068.
 */
class Unk_806B94B8 : public nw4r::ef::Emitter {
public:
    Unk_806B94B8();  // 0x80244ABC
    ~Unk_806B94B8(); // 0x80244A6C

    //! Parameter overrides of the owning effect (placeholder name)
    Unk_806B9908* fn_80244758();

private:
    u8 mUnk138[0x154 - 0x138]; // at 0x138
    Unk_806B9908* mUnk154;     // at 0x154
};

// nw4r::ef::MemoryManager configuration
#define NW4R_EF_MEMORY_MANAGER_CONFIGURED
#define NW4R_EF_MEMORY_MANAGER_TMP_CLASS RPSysEffectMemoryManagerTmp
#define NW4R_EF_MEMORY_MANAGER_CLASS RPSysEffectMemoryManager
#define NW4R_EF_MEMORY_MANAGER_TEFFECT Unk_806B98E0
#define NW4R_EF_MEMORY_MANAGER_TEMITTER Unk_806B94B8
#define NW4R_EF_MEMORY_MANAGER_TPARTICLEMANAGER RPSysParticleManager

// Include with NW4R_EF_MEMORY_MANAGER_CONFIGURED to get ef_memorymanagerimpl.h
#include <nw4r/ef.h>

#endif
