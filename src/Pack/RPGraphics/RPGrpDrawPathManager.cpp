// g3d_gpu.h (`static const u8 cm2hw[]`) emits a stray .sdata2 entry that this
// object lacks. Pre-define its include guard so it is skipped; nothing here uses it.

// Class definition order controls the weak vtable layout.
#include <Pack/RPGraphics/RPGrpDrawPathManager.h>
#include <Pack/RPGraphics/RPGrpDrawPathSV.h>
#include <Pack/RPGraphics/RPGrpDrawPathHDR.h>
#include <Pack/RPGraphics/RPGrpDrawPathDOF.h>
#include <Pack/RPGraphics/RPGrpDrawPathBloom.h>
#include <Pack/RPGraphics/RPGrpDrawPathXluSnap.h>
#include <Pack/RPGraphics/RPGrpDrawPathLightMap.h>
#include <Pack/RPGraphics/RPGrpDrawPathShadowTexture.h>
#include <Pack/RPKernel/RPSysEffectMgr.h>

RPGrpDrawPathManager*
RPGrpDrawPathManager::Construct(u32 pathFlags, RPGrpModelScene* pModelScene) {

    return new RPGrpDrawPathManager(pathFlags, pModelScene);
}

// TODO: unknown singleton (sbss 0x806F4D10) and its getters
extern "C" {
s32 fn_8023D7F8(void* pObj);
s32 fn_8023D7F0(void* pObj);
}

RPGrpDrawPathManager::RPGrpDrawPathManager(u32 pathFlags,
                                           RPGrpModelScene* pModelScene)
    : unkC(1),
      mpModelScene(pModelScene),
      unk14(0) {

    // TODO: RPGrpModelScene member at 0x9C
    EGG::ScnRenderer* pRenderer = *reinterpret_cast<EGG::ScnRenderer**>(
        reinterpret_cast<u8*>(pModelScene) + 0x9C);

    for (int i = 0; i < EDrawPath_Max; i++) {
        mpDrawPaths[i] = NULL;
    }

    bool sv2 = false;

    if (pathFlags & EFlag_DrawPathSV) {
        mpDrawPaths[EDrawPath_SV] =
            RPGrpDrawPath::Construct<RPGrpDrawPathSV>(pRenderer, false);
    } else if (pathFlags & EFlag_DrawPathSV2) {
        RPGrpDrawPathSV* pSV =
            RPGrpDrawPath::Construct<RPGrpDrawPathSV>(pRenderer, true);
        mpDrawPaths[EDrawPath_SV] = pSV;
        sv2 = true;
        // TODO: EGG::DrawPathBase member at 0x18
        *reinterpret_cast<u16*>(reinterpret_cast<u8*>(pSV->mpSV) + 0x18) |= 2;
    }

    if (pathFlags & EFlag_DrawPathHDR) {
        mpDrawPaths[EDrawPath_HDR] =
            RPGrpDrawPath::Construct<RPGrpDrawPathHDR>(pRenderer);
    }

    if (pathFlags & EFlag_DrawPathDOF) {
        mpDrawPaths[EDrawPath_DOF] =
            RPGrpDrawPath::Construct<RPGrpDrawPathDOF>(pRenderer);
    }

    if (pathFlags & EFlag_DrawPathBloom) {
        mpDrawPaths[EDrawPath_Bloom] =
            RPGrpDrawPath::Construct<RPGrpDrawPathBloom>(pRenderer);

        if (pRenderer->Unk_8024D6D0() != NULL) {
            // TODO: EGG::DrawPathBase member at 0x18
            *reinterpret_cast<u16*>(
                reinterpret_cast<u8*>(pRenderer->Unk_8024D6D0()) + 0x18) |= 2;
        }
    }

    if (pathFlags & EFlag_DrawPathXluSnap) {
        mpDrawPaths[EDrawPath_XluSnap] =
            RPGrpDrawPath::Construct<RPGrpDrawPathXluSnap>(pRenderer);
    }

    if (pathFlags & EFlag_DrawPathLightMap) {
        mpDrawPaths[EDrawPath_LightMap] = reinterpret_cast<RPGrpDrawPath*>(
            RPGrpDrawPath::Construct<RPGrpDrawPathLightMap>(pRenderer));
    }

    if (pathFlags & EFlag_DrawPathShadowTexture) {
        mpDrawPaths[EDrawPath_ShadowTexture] = reinterpret_cast<RPGrpDrawPath*>(
            RPGrpDrawPath::Construct<RPGrpDrawPathShadowTexture>(pRenderer));
    }

    createScnProc(8, NULL);

    u32 timing[8] = {3, 4, 0, sv2 ? 4 : 1, sv2 ? 5 : 2, 7, 9, 7};

    for (int i = 0; i < 8; i++) {
        u16 prio = pRenderer->getLocalPriorityMax();
        pRenderer->setLocalPriorityScnProc(this, timing[i], prio, i);
    }
}

static const u16 sUnkTiming[] = {3, 6, 0, 1};

void RPGrpDrawPathManager::Unk_8024D360() {
    EGG::ScnRenderer* pRenderer;
    s32 prio = fn_8023D7F8(RPSysEffectMgr::instance());
    if (prio < 0) {
        prio = 0;
    } else if (prio > 255) {
        prio = 255;
    }

    // TODO: RPGrpModelScene member at 0x9C
    pRenderer = *reinterpret_cast<EGG::ScnRenderer**>(
        reinterpret_cast<u8*>(mpModelScene) + 0x9C);

    pRenderer->setLocalPriorityScnProc(
        this, sUnkTiming[fn_8023D7F0(RPSysEffectMgr::instance())], prio, 7);
}

// TODO: type of the unk14 callback (draw method in vtable slot 0xC)
struct UnkScnProc {
    virtual ~UnkScnProc();
    virtual void Unk_0xC(u16 idx);
};

void RPGrpDrawPathManager::scnProcDraw(u16 idx) {
    if (unk14 != 0) {
        if (idx == 4 && (mpDrawPaths[EDrawPath_SV] == NULL ||
                           !mpDrawPaths[EDrawPath_SV]->IsEnable())) {
            return;
        }

        reinterpret_cast<UnkScnProc*>(unk14)->Unk_0xC(idx);
    }
}


template <typename T>
T* RPGrpDrawPath::Construct(EGG::ScnRenderer* pRenderer) {
    return new T(pRenderer);
}

template <typename T>
T* RPGrpDrawPath::Construct(EGG::ScnRenderer* pRenderer, bool second) {
    return new T(pRenderer, second);
}

