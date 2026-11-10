// g3d_gpu.h (`static const u8 cm2hw[]`) emits a stray .sdata2 entry that this
// object lacks; nothing here uses it, so pre-define its include guard.
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPGraphics/RPGrpModelMisc.h>
#include <Pack/RPGraphics.h>

#include <egg/core.h>
#include <egg/gfxe.h>

RPGrpModelManager* RPGrpModelManager::spCurrent = NULL;

void RPGrpModelMisc::GetBinaryInner(Bin* /* pBinary */) const {}

void RPGrpModelMisc::SetBinaryInner(const Bin& /* rBinary */) {
    // Stubbed out in revision 1
}

RPGrpModelMisc::~RPGrpModelMisc() {}

u8 RPGrpModelMisc::GetVersion() const {
    return VERSION;
}

RPGrpModelManager::RPGrpModelManager(EGG::Allocator* pAllocator,
                                     EGG::Allocator* pSceneAllocator)
    : mpAllocator(pAllocator),
      mpSceneAllocator(pSceneAllocator),
      unk50(false) {

    RPGrpModel::spGenList = NULL;

    mpResManager = new RPGrpModelResManager();
    mpResManager->Configure();

    for (int i = 0; i < MAX_SCENE; i++) {
        mpModelScenes[i] = NULL;
    }

}

void RPGrpModelManager::fn_801AE21C() {
    spCurrent = this;
    RPGrpModelResManager::spCurrent = mpResManager;
    RPGrpModel::SetAllocator(mpAllocator);
    RPGrpModel::spEntryTail = NULL;
    RPGrpModel::spEntryHead = NULL;
    RPGrpModelScene::spAllocator = mpSceneAllocator;
    EGG::G3DUtility::setAllocator(mpAllocator);
}

void RPGrpModelManager::fn_801AE1B4(u8 drawScene, u32 arg1, u8 viewNum,
                                    RPGrpLightManager* pLightManager,
                                    RPGrpFogManager* pFogManager) {
    mpModelScenes[drawScene] =
        new RPGrpModelScene(arg1, viewNum, pLightManager, pFogManager);
}

void RPGrpModelManager::fn_801AE160() {
    for (int i = 0; i < MAX_SCENE; i++) {
        if (mpModelScenes[i] != NULL) {
            mpModelScenes[i]->fn_801B1DBC();
        }
    }
}

void RPGrpModelManager::fn_801AE070() {
    if (unk50) {
        return;
    }

    int i = 0;
    RPGrpModelScene** ppScene = mpModelScenes;
    for (; i < MAX_SCENE; i++, ppScene++) {
        if (*ppScene != NULL) {
            (*ppScene)->CalcView();
        }
    }

    if (RPGrpModel::spEntryTail != NULL) {
        RPGrpModel::spEntryTail->mpEntryNext = NULL;

        for (RPGrpModel* p = RPGrpModel::spEntryHead; p != NULL;
             p = p->mpEntryNext) {
            mpModelScenes[p->mDrawScene]->fn_801B19F0(p);
        }

        RPGrpModel::spEntryTail = NULL;
        RPGrpModel::spEntryHead = NULL;
    }

    for (int i = 0; i < MAX_SCENE; i++) {
        if (mpModelScenes[i] != NULL) {
            mpModelScenes[i]->CalcDrawList();
        }
    }
}

void RPGrpModelManager::fn_801ADFD0() {
    for (int i = 0; i < MAX_SCENE; i++) {
        if (mpModelScenes[i] != NULL) {
            // TODO: EGG::ScnRootEx::mpScnRoot is protected
            nw4r::g3d::ScnRoot* pScnRoot = *reinterpret_cast<nw4r::g3d::ScnRoot**>(
                mpModelScenes[i]->mpScnRootEx);

            pScnRoot->SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_CALC_WORLD,
                                      true);
            mpModelScenes[i]->mpScnRootEx->CalcWorld();
            pScnRoot = *reinterpret_cast<nw4r::g3d::ScnRoot**>(
                mpModelScenes[i]->mpScnRootEx);
            pScnRoot->SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_CALC_WORLD,
                                      false);
        }
    }
}

void RPGrpModelManager::fn_801ADF78() {
    RPGrpModelScene::fn_801B23E0();

    for (int i = 0; i < MAX_SCENE; i++) {
        if (mpModelScenes[i] != NULL) {
            mpModelScenes[i]->fn_801B1C44();
        }
    }
}

void RPGrpModelManager::fn_801ADF18() {
    for (int i = 0; i < MAX_SCENE; i++) {
        if (mpModelScenes[i] != NULL) {
            mpModelScenes[i]->DrawFinish();
        }
    }
}

void RPGrpModelManager::fn_801ADEC8() {
    mpResManager->TerminateAll();

    if (spCurrent == this) {
        RPGrpModel::SetAllocator(NULL);
        RPGrpModelScene::spAllocator = NULL;
        RPGrpModelResManager::spCurrent = NULL;
        spCurrent = NULL;
    }
}

void RPGrpModelManager::fn_801ADEB0() {
    RPGrpModel::SetAllocator(NULL);
    RPGrpModelScene::spAllocator = NULL;
    RPGrpModelResManager::spCurrent = NULL;
    spCurrent = NULL;
}

RPGrpDrawPathManager*
RPGrpModelManager::GetDrawPathManager(u8 drawScene) const {
    return mpModelScenes[drawScene]->mpDrawPathManager;
}

EGG::LightManager* RPGrpModelManager::GetLightManager(u8 drawScene) const {
    return reinterpret_cast<EGG::LightManager*>(
        mpModelScenes[drawScene]->mpLightManager);
}

RPGrpFogManager* RPGrpModelManager::GetFogManager(u8 drawScene) const {
    return mpModelScenes[drawScene]->mpFogManager;
}
