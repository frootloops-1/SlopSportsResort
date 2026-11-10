// g3d_gpu.h (`static const u8 cm2hw[]`) emits a stray .sdata2 entry that this
// object lacks. Pre-define its include guard so it is skipped; nothing here uses it.
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <egg/core.h>

#include <nw4r/ef.h>

#include <revolution/MTX.h>

// Functions are defined in reverse address order: this unit's compiler emits
// .text in reverse source order (the destructor at 0x8023C6F8 is last here).

RPSysEffectMgr* RPSysEffectMgr::spInstance = NULL;

void RPSysEffectMgr::CreateInstance() {
    spInstance = new RPSysEffectMgr();
}

// Resort: 0x8023D800
void RPSysEffectMgr::fn_8023D800(s32 arg0, u32 arg1) {
    mUnk14 = arg0;
    mUnk18 = arg1;
}

// Resort: 0x8023D7F8 / 0x8023D7F0. Kept with C linkage: the Matching unit
// RPGrpDrawPathManager declares them as extern "C" fn_8023D7F8/fn_8023D7F0.
extern "C" s32 fn_8023D7F8(RPSysEffectMgr* pMgr) {
    return pMgr->mUnk14;
}

extern "C" u32 fn_8023D7F0(RPSysEffectMgr* pMgr) {
    return pMgr->mUnk18;
}

void RPSysEffectMgr::fn_8023D744(const nw4r::math::VEC3& rPos,
                                 const nw4r::math::MTX34& rMtx, f32 far,
                                 f32 near) {
    nw4r::ef::EffectSystem::GetInstance()->SetProcessCamera(rPos, rMtx, far,
                                                            near);

    for (int i = 0; i < EDrawScene_Max; i++) {
        if (mpEffectCreators[i] != NULL &&
            mpEffectCreators[i]->isSlowSystem()) {

            mpEffectCreators[i]->fn_8023F56C(rPos, rMtx, far, near);
        }
    }
}

void RPSysEffectMgr::fn_8023D674(const char* pTexName, void* pTexture,
                                 const EfbTexData& rData) {
    nw4r::ef::Resource* pResource = nw4r::ef::Resource::GetInstance();

    for (int i = 0; i < EDrawScene_Max; i++) {
        if (mpEffectCreators[i] == NULL) {
            continue;
        }

        for (int j = 0; j < RPSysEffectCreator::RESOURCE_MAX; j++) {
            nw4r::ef::TextureProject* pProject =
                mpEffectCreators[i]->fn_8023F2B0(j);

            if (pProject == NULL) {
                continue;
            }

            nw4r::ef::ResTexture res =
                pResource->FindTexture(pTexName, pProject);

            if (res.IsValid()) {
                res.ptr()->format = rData.format;
                res.ptr()->width = rData.width;
                res.ptr()->height = rData.height;
                res.ptr()->texture = static_cast<u8*>(pTexture);
            }
        }
    }
}

GXColor* RPSysEffectMgr::fn_8023D66C(u32 idx) {
    return fn_8024AAFC(idx);
}

void RPSysEffectMgr::fn_8023D628(u8* pData, u32 idx) {
    nw4r::ut::Color color(0xFFFFFFFF);
    fn_8023C89C(pData, &color);
    fn_8024AB10(&color, idx);
}

void RPSysEffectMgr::fn_8023D604(u32 groupBits, u32 drawGroup) {
    mUnk1C[drawGroup].setBit((groupBits >> 4) & 0xF);
}

bool RPSysEffectMgr::fn_8023D5DC(u32 groupBits, u32 drawGroup) const {
    return mUnk1C[drawGroup].onBit((groupBits >> 4) & 0xF);
}

bool RPSysEffectMgr::fn_8023D5C4(u32 drawGroup) const {
    return !mUnk1C[drawGroup].isZero();
}

void RPSysEffectMgr::setCreator(RPSysEffectCreator* pCreator, u32 drawScene) {
    if (pCreator == NULL) {
        return;
    }

    mpEffectCreators[drawScene] = pCreator;
}

void RPSysEffectMgr::resetCreator(RPSysEffectCreator* pCreator) {
    if (pCreator == NULL) {
        return;
    }

    for (int i = 0; i < EDrawScene_Max; i++) {
        if (mpEffectCreators[i] == pCreator) {
            mpEffectCreators[i] = NULL;
            return;
        }
    }
}

void RPSysEffectMgr::stopAllEffect() {
    nw4r::ef::EffectSystem* pSystem = nw4r::ef::EffectSystem::GetInstance();

    for (u32 i = 0; i < RPSysEffectDefine::MAX_GROUP_ID; i++) {
        pSystem->RetireEmitterAll(i);
        pSystem->RetireParticleAll(i);
    }

    for (int i = 0; i < EDrawScene_Max; i++) {
        if (mpEffectCreators[i] == NULL) {
            continue;
        }

        if (mpEffectCreators[i]->isSlowSystem()) {
            mpEffectCreators[i]->stopAllEffect();
        }
    }
}

void RPSysEffectMgr::fn_8023D454() {
    mUnk10 = true;
    mUnk11 = false;
    mUnk14 = -1;
    mUnk18 = 1;

    for (int i = 0; i < 16; i++) {
        mUnk1C[i].makeAllZero();
    }

    for (int i = 0; i < 3; i++) {
        nw4r::ut::Color color(0xFFFFFFFF);
        fn_8024AB10(&color, i);
    }

    fn_8024AAF4(FALSE);
}

void RPSysEffectMgr::update(ECalcSetting setting) {
    (void)nw4r::ef::EffectSystem::GetInstance();

    for (int i = 0; i < EDrawScene_Max; i++) {
        if (mpEffectCreators[i] == NULL) {
            continue;
        }

        if (i == EDrawScene_Cursor) {
            mpEffectCreators[i]->fn_8023F52C();
        } else if (setting == ECalcSetting_All && mUnk10) {
            mpEffectCreators[i]->fn_8023F52C();
        }
    }

    fn_8024AAF4(FALSE);
}

void RPSysEffectMgr::setCaptureEfb(void* pTexture, const EfbTexData& rData) {
    fn_8023D674("dummy_tex", pTexture, rData);
}

void RPSysEffectMgr::draw(const nw4r::math::MTX34& rViewMtx, u32 drawGroup,
                          u32 drawScene) {
    if (drawGroup < EDrawGroup_16) {
        nw4r::ef::DrawInfo drawInfo;
        drawInfo.SetViewMtx(rViewMtx);
        drawInfo.SetProjMtx(fn_8023C900());

        for (int i = 0; i < EDrawScene_Max; i++) {
            if (mpEffectCreators[i] == NULL) {
                continue;
            }

            mpEffectCreators[i]->fn_8023F2C0(
                drawInfo, drawGroup, drawScene,
                mUnk11 && i != EDrawScene_Cursor && drawScene != 0x60 &&
                    drawScene != 0x70);
        }
    }
}

nw4r::ef::Effect* RPSysEffectMgr::createEffect(const char* pName, u32 drawGroup,
                                               u32 drawScene) {
    return mpEffectCreators[drawScene]->createEffect(pName, drawGroup);
}

u32 RPSysEffectMgr::createMemoryManager(EffectArg* pArg) {
    u32 workSize = RPSysEffectMemoryManager::CalcMemorySize( //
        pArg->maxEffect,                                     //
        pArg->maxEmitter,                                    //
        pArg->maxParticleManager,                            //
        pArg->maxParticle,                                   //
        RPSysEffectDefine::MAX_GROUP_ID);

    void* pEffectWork = EGG::Heap::alloc(workSize, 32, pArg->pHeap);

    RPSysEffectMemoryManager* pMemoryManager =
        new (pArg->pHeap) RPSysEffectMemoryManager( //
            pEffectWork,                            //
            workSize,                               //
            pArg->maxEffect,                        //
            pArg->maxEmitter,                       //
            pArg->maxParticleManager,               //
            pArg->maxParticle);

    nw4r::ef::EffectSystem::GetInstance()->SetMemoryManager(
        pMemoryManager, RPSysEffectDefine::MAX_GROUP_ID);

    return workSize;
}

RPSysEffectCreator* RPSysEffectMgr::fn_8023C9D4(u32 drawScene) const {
    return mpEffectCreators[drawScene];
}

nw4r::math::MTX34 RPSysEffectMgr::fn_8023C900() const {
    nw4r::math::MTX34 proj;

    RPGrpScreen* pScreen = RPGrpRenderer::GetCurrentScreen();
    RPGrpView* pView = RPGrpRenderer::GetCurrentView();

    if (pView->GetProjType() == RPGrpView::EProjType_Persp) {
        C_MTXLightPerspective(proj, pScreen->GetFovy(), pScreen->GetAspect(),
                              0.5f, -0.5f, 0.5f, 0.5f);
    } else {
        f32 cx = pScreen->GetWidth() / 2.0f;
        f32 cy = pScreen->GetHeight() / 2.0f;
        C_MTXLightOrtho(proj, cy, -cy, -cx, cx, 0.5f, -0.5f, 0.5f, 0.5f);
    }

    return proj;
}

void RPSysEffectMgr::fn_8023C89C(u8* pData, GXColor* pOut) const {
    EGG::RamStream stream(pData, 0x20);

    pOut->r = stream.read_u8();
    pOut->g = stream.read_u8();
    pOut->b = stream.read_u8();
}

RPSysEffectMgr::RPSysEffectMgr() {
    for (int i = 0; i < EDrawScene_Max; i++) {
        mpEffectCreators[i] = NULL;
    }

    mUnkC = NULL;
    fn_8023D454();

    nw4r::ef::EffectSystem* pSystem = nw4r::ef::EffectSystem::GetInstance();
    pSystem->SetXFFlushSafe(true);

    nw4r::math::MTX34 camMtx;
    PSMTXIdentity(camMtx);
    pSystem->SetProcessCamera(nw4r::math::VEC3(0.0f, 0.0f, 1000.0f), camMtx,
                              1.0f, 1000.0f);

    pSystem->mUnkC068 = new Unk_806B94B8();
}

RPSysEffectMgr::~RPSysEffectMgr() {
    stopAllEffect();

    for (int i = 0; i < EDrawScene_Max; i++) {
        if (mpEffectCreators[i] != NULL) {
            delete mpEffectCreators[i];
        }
    }

    nw4r::ef::Resource::GetInstance()->Initialize();
    EGG::Heap::free(mUnkC, NULL);
}
