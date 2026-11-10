#ifndef NW4R_EF_EFFECT_SYSTEM_H
#define NW4R_EF_EFFECT_SYSTEM_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_creationqueue.h>
#include <nw4r/ef/ef_random.h>
#include <nw4r/math.h>

namespace nw4r {
namespace ef {

// Forward declarations
class ActivityList;
class DrawInfo;
class DrawOrderBase;
class DrawStrategyBuilder;
class Emitter;
struct EmitterResource;
class EmitFormBuilder;
class MemoryManagerBase;

class EffectSystem {
private:
    MemoryManagerBase* mMemoryManager; // at 0x0

public:
    DrawOrderBase* mDrawOrderFunc;             // at 0x4
    DrawStrategyBuilder* mDrawStrategyBuilder; // at 0x8
    EmitFormBuilder* mEmitFormBuilder;         // at 0xC
    CreationQueue mCreationQueue;              // at 0x10
    // Resort: offsets below verified against Initialize (0x80116C80) and
    // the ctor (0x80116B70); the creation queue grew to 0xC004 bytes.
    u32 mMaxGroupID;                           // at 0xC014
    ActivityList* mActivityList;               // at 0xC018
    Random mRandom;                            // at 0xC01C
    math::VEC3 mProcessCameraPos;              // at 0xC020
    math::MTX34 mProcessCameraMtx;             // at 0xC02C
    f32 mProcessCameraFar;                     // at 0xC05C
    f32 mProcessCameraNear;                    // at 0xC060
    bool mXFFlushSafe;                         // at 0xC064
    // Resort: 0x158-byte emitter-like object (ctor 0x80244ABC), created by
    // RPSysEffectMgr's ctor; zeroed by the EffectSystem ctor.
    Emitter* mUnkC068; // at 0xC068

    static bool mDisplayVersion;
    static EffectSystem instance;

    // Resort: .bss 0x80794EF8 (constructed in the same __sinit as
    // `instance`); read by SortEffectOperatorZ (0x80117480).
    static DrawInfo Unk_80794EF8;

public:
    static EffectSystem* GetInstance();

    EffectSystem();
    ~EffectSystem();

    bool Initialize(u32 maxGroupID);
    bool Closing(Effect* pEffect);

    Effect* CreateEffect(const char* pName, u32 groupID, u16 calcRemain);
    // Resort: 0x80116E50
    Effect* CreateEffect(EmitterResource* pResource, u32 groupID,
                         u16 calcRemain);
    u32 RetireEffect(Effect* pEffect);

    u32 RetireEffectAll(u32 groupID);
    u32 RetireEmitterAll(u32 groupID);
    u32 RetireParticleAll(u32 groupID);

    void Calc(u32 groupID, bool onlyBillboard);
    void Draw(const DrawInfo& rInfo, u32 groupID);

    // Resort: 0x80117220
    void SetProcessCamera(const math::VEC3& rPos, const math::MTX34& rMtx,
                          f32 far, f32 near);
    // Resort: 0x80117300
    void SortEffect(bool (*pCompare)(const Effect*, const Effect*),
                    u32 groupID);
    // Resort: 0x80117480
    static bool SortEffectOperatorZ(const Effect* pLhs, const Effect* pRhs);

    MemoryManagerBase* GetMemoryManager() const {
        return mMemoryManager;
    }
    void SetMemoryManager(MemoryManagerBase* pManager, u32 maxGroupID) {
        mMemoryManager = pManager;

        if (mMemoryManager != NULL) {
            Initialize(maxGroupID);
        } else {
            // Resort: RPSysEffectMgr::createMemoryManager 0x8023CDF0
            mMaxGroupID = 0;
            mActivityList = NULL;
        }
    }

    void SetXFFlushSafe(bool safe) {
        mXFFlushSafe = safe;
    }
};

} // namespace ef
} // namespace nw4r

#endif
