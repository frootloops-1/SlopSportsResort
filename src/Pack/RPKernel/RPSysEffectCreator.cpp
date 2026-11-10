// g3d_gpu.h (`static const u8 cm2hw[]`) emits a stray .sdata2 entry that this
// object lacks. Pre-define its include guard so it is skipped; nothing here uses it.
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPKernel.h>

#include <egg/core.h>

#include <nw4r/ef.h>
#include <nw4r/ut.h>

#include <cstring>

#define MY_EPSILON 0.000001f

// Functions are defined in reverse address order: this unit's compiler emits
// .text in reverse source order (update 0x8023EB18 first, createSlowSystem
// last, then the weak parameter constructors at 0x8023FE3C/0x8023FE40).

void RPSysEffectCreator::createSlowSystem() {
    u32 workSize = RPSysEffectMemoryManager::CalcMemorySize( //
        SLOW_MAX_EFFECT,                                     //
        SLOW_MAX_EMITTER,                                    //
        SLOW_MAX_PARTICLE_MANAGER,                           //
        SLOW_MAX_PARTICLE,                                   //
        RPSysEffectDefine::MAX_GROUP_ID);

    void* pEffectWork = EGG::Heap::alloc(workSize, 32, NULL);

    RPSysEffectMemoryManager* pMemoryManager =
        new RPSysEffectMemoryManager( //
            pEffectWork,              //
            workSize,                 //
            SLOW_MAX_EFFECT,          //
            SLOW_MAX_EMITTER,         //
            SLOW_MAX_PARTICLE_MANAGER, //
            SLOW_MAX_PARTICLE);

    mpSlowSystem = new nw4r::ef::EffectSystem();
    mpSlowSystem->SetMemoryManager(pMemoryManager,
                                   RPSysEffectDefine::MAX_GROUP_ID);

    for (int i = 0; i < ESaveBuffer_Max; i++) {
        mpEmitterParamSave[i] = //
            new nw4r::ef::EmitterParameter[SLOW_MAX_EMITTER];
        mpParticleParamSave[i] = //
            new nw4r::ef::ParticleParameter[SLOW_MAX_PARTICLE];
    }

    nw4r::math::MTX34 camMtx;
    nw4r::math::MTX34Identity(&camMtx);
    mpSlowSystem->SetProcessCamera(nw4r::math::VEC3(0.0f, 0.0f, 1000.0f),
                                   camMtx, 1.0f, 1000.0f);

    mpSlowSystem->mUnkC068 = new Unk_806B94B8();
}

void RPSysEffectCreator::setFrameRate(f32 frameRate) {
    if (frameRate > 1.0f - MY_EPSILON) {
        mFrameRate = 1.0f - MY_EPSILON;

    } else if (frameRate < MY_EPSILON) {
        mFrameRate = MY_EPSILON;

    } else {
        mFrameRate = frameRate;
    }
}

bool RPSysEffectCreator::isSlowSystem() const {
    return mpSlowSystem != NULL;
}

bool RPSysEffectCreator::fn_8023F8A0(void* pEffectProject,
                                     void* pTextureProject, int idx) {
    if (mpEffectProject[idx] == NULL && mpTextureProject[idx] == NULL) {
        nw4r::ef::Resource* pResource = nw4r::ef::Resource::GetInstance();

        mpEffectProject[idx] = pResource->Add(static_cast<u8*>(pEffectProject));
        mpTextureProject[idx] =
            pResource->AddTexture(static_cast<u8*>(pTextureProject));

        pResource->RelocateCommand();
        return true;
    }

    return false;
}

void RPSysEffectCreator::fn_8023F800() {
    bool relocate = false;
    nw4r::ef::Resource* pResource = nw4r::ef::Resource::GetInstance();

    for (int i = 0; i < RESOURCE_MAX; i++) {
        if (mpEffectProject[i] != NULL) {
            pResource->RemoveEffectProject(mpEffectProject[i]);
            mpEffectProject[i] = NULL;
            relocate = true;
        }

        if (mpTextureProject[i] != NULL) {
            pResource->RemoveTextureProject(mpTextureProject[i]);
            mpTextureProject[i] = NULL;
            relocate = true;
        }
    }

    if (relocate) {
        pResource->RelocateCommand();
    }
}

RPSysEffectCreator::RPSysEffectCreator(u32 drawScene) {
    mBaseGroupID = drawScene << 7;

    for (int i = 0; i < RESOURCE_MAX; i++) {
        mpEffectProject[i] = NULL;
        mpTextureProject[i] = NULL;
    }

    mBackSaveBuffer = ESaveBuffer_2nd;
    mIsSlowEffect = false;

    mFrame = 0.0f;
    mFrameRate = 1.0f - MY_EPSILON;

    mpSlowSystem = NULL;

    for (int i = 0; i < ESaveBuffer_Max; i++) {
        mpEmitterParamSave[i] = NULL;
        mpParticleParamSave[i] = NULL;
    }
}

RPSysEffectCreator::~RPSysEffectCreator() {
    stopAllEffect();
    fn_8023F800();
}

void RPSysEffectCreator::stopAllEffect() {
    nw4r::ef::EffectSystem* pSystem = nw4r::ef::EffectSystem::GetInstance();

    for (int i = 0; i < RPSysEffectMgr::EDrawGroup_Max * 2; i++) {
        u32 groupID = mBaseGroupID | i;
        pSystem->RetireEmitterAll(groupID);
        pSystem->RetireParticleAll(groupID);
    }

    if (mpSlowSystem != NULL) {
        for (int i = 0; i < RPSysEffectMgr::EDrawGroup_Max * 2; i++) {
            u32 groupID = mBaseGroupID | i;
            mpSlowSystem->RetireEmitterAll(groupID);
            mpSlowSystem->RetireParticleAll(groupID);
        }
    }
}

nw4r::ef::Effect* RPSysEffectCreator::createEffect(const char* pName,
                                                   u32 drawGroup) {
    nw4r::ef::ResEmitter res =
        nw4r::ef::Resource::GetInstance()->FindEmitter(pName, NULL);
    nw4r::ef::EmitterResource* pResource = res.ptr();

    u32 flags = pResource->GetEmitterDesc()->userdata[2] << 8 |
                pResource->GetEmitterDesc()->userdata[3];

    u32 groupBits = fn_8023F248(flags);

    RPSysEffectMgr::instance()->fn_8023D604(groupBits, drawGroup);

    u32 groupID = drawGroup | (groupBits | mBaseGroupID);

    if (mpSlowSystem != NULL &&
        flags & RPSysEffectDefine::EUserFlag_SlowSystem) {

        return mpSlowSystem->CreateEffect(pResource, groupID, 0);
    } else {
        return nw4r::ef::EffectSystem::GetInstance() //
            ->CreateEffect(pResource, groupID, 0);
    }
}

void RPSysEffectCreator::fn_8023F56C(const nw4r::math::VEC3& rPos,
                                     const nw4r::math::MTX34& rMtx, f32 far,
                                     f32 near) {
    if (mpSlowSystem != NULL) {
        mpSlowSystem->SetProcessCamera(rPos, rMtx, far, near);
    }
}

void RPSysEffectCreator::fn_8023F52C() {
    fn_8023F154(nw4r::ef::EffectSystem::GetInstance());
    update();
}

// Z-sorts a system's group against the given view (the system is evaluated
// before the DrawInfo copy, so it is not reloaded).
static inline void SortEffectZ(nw4r::ef::EffectSystem* pSystem,
                               const nw4r::ef::DrawInfo& rDrawInfo,
                               u32 groupID) {
    nw4r::ef::EffectSystem::Unk_80794EF8 = rDrawInfo;
    pSystem->SortEffect(nw4r::ef::EffectSystem::SortEffectOperatorZ, groupID);
}

void RPSysEffectCreator::fn_8023F2C0(const nw4r::ef::DrawInfo& rDrawInfo,
                                     u32 drawGroup, u32 drawScene,
                                     bool sort) {
    drawGroup |= drawScene;
    u32 groupID = drawGroup | mBaseGroupID;
    nw4r::ef::EffectSystem* pSystem = nw4r::ef::EffectSystem::GetInstance();

    if (sort) {
        SortEffectZ(pSystem, rDrawInfo, groupID);
    }

    pSystem->Draw(rDrawInfo, groupID);

    if (mpSlowSystem != NULL) {
        if (sort) {
            SortEffectZ(mpSlowSystem, rDrawInfo, groupID);
        }

        mpSlowSystem->Draw(rDrawInfo, groupID);
    }
}

nw4r::ef::TextureProject* RPSysEffectCreator::fn_8023F2B0(int idx) const {
    return mpTextureProject[idx];
}

u32 RPSysEffectCreator::fn_8023F248(u16 flags) const {
    if (flags & RPSysEffectDefine::EUserFlag_15) {
        return (flags & RPSysEffectDefine::EUserFlag_0) ? 0x70 : 0x60;
    }

    if (flags & RPSysEffectDefine::EUserFlag_0) {
        if (flags & 0x2) {
            return 0x10;
        }

        return (flags & 0x2000) ? 0x20 : 0x00;
    }

    if (flags & 0x2) {
        return 0x40;
    }

    return (flags & 0x2000) ? 0x50 : 0x30;
}

void RPSysEffectCreator::fn_8023F154(nw4r::ef::EffectSystem* pSystem) {
    nw4r::ef::Effect* effects[1024];

    RPSysEffectMgr* pMgr = RPSysEffectMgr::instance();

    for (u32 i = 0; i < 16; i++) {
        if (!pMgr->fn_8023D5C4(i)) {
            continue;
        }

        for (u32 j = 0; j < 0x80; j += 0x10) {
            if (!pMgr->fn_8023D5DC(j, i)) {
                continue;
            }

            nw4r::ut::List* pList =
                &pSystem->mActivityList[i | (j | mBaseGroupID)].mActiveList;

            u16 num = nw4r::ef::UtlistToArray(
                pList, reinterpret_cast<void**>(effects), pList->numObjects);

            for (u16 k = 0; k < num; k++) {
                effects[k]->Calc(false);
            }
        }
    }

    pSystem->GetMemoryManager()->GarbageCollection();
}

void RPSysEffectCreator::update() {
    if (mpSlowSystem == NULL) {
        return;
    }

    const nw4r::ut::List *pListEmitter, *pListParticle;

    const nw4r::ef::EmitterParameter* pLoadEmitter =
        mpEmitterParamSave[mBackSaveBuffer == ESaveBuffer_1st
                               ? ESaveBuffer_2nd
                               : ESaveBuffer_1st];

    const nw4r::ef::ParticleParameter* pLoadParticle =
        mpParticleParamSave[mBackSaveBuffer == ESaveBuffer_1st
                                ? ESaveBuffer_2nd
                                : ESaveBuffer_1st];

    nw4r::ef::EmitterParameter* pSaveEmitter =
        mpEmitterParamSave[mBackSaveBuffer];

    nw4r::ef::ParticleParameter* pSaveParticle =
        mpParticleParamSave[mBackSaveBuffer];

    RPSysEffectMemoryManager* pMemoryManager =
        static_cast<RPSysEffectMemoryManager*>(
            mpSlowSystem->GetMemoryManager());

    pListEmitter = &pMemoryManager->mEmitterOM->mLeasedList;
    pListParticle = &pMemoryManager->mParticleOM->mLeasedList;

    if (mIsSlowEffect) {
        fn_8023F154(mpSlowSystem);

        RP_NW4R_LIST_FOREACH (nw4r::ef::Emitter, it, *pListEmitter) {
            std::memcpy(&pSaveEmitter[it->GetObjectIdx()], &it->mParameter,
                        sizeof(nw4r::ef::EmitterParameter));
        }

        RP_NW4R_LIST_FOREACH (nw4r::ef::Particle, it, *pListParticle) {
            std::memcpy(&pSaveParticle[it->GetObjectIdx()], &it->mParameter,
                        sizeof(nw4r::ef::ParticleParameter));
        }
    }

    RP_NW4R_LIST_FOREACH (nw4r::ef::Emitter, it, *pListEmitter) {
        const nw4r::ef::EmitterParameter* pT0 =
            &pLoadEmitter[it->GetObjectIdx()];

        const nw4r::ef::EmitterParameter* pT1 =
            &pSaveEmitter[it->GetObjectIdx()];

        if (it->mTick <= ESaveBuffer_Max - 1) {
            it->mParameter.mComFlags |=
                nw4r::ef::EmitterDesc::CMN_FLAG_DISABLE_DRAW;

            continue;
        }

        if (it->mTick == ESaveBuffer_Max) {
            it->mParameter.mComFlags &=
                ~nw4r::ef::EmitterDesc::CMN_FLAG_DISABLE_DRAW;
        }

        // clang-format off
        it->mParameter.mRotate.x = pT0->mRotate.x + (pT1->mRotate.x - pT0->mRotate.x) * mFrame;
        it->mParameter.mRotate.y = pT0->mRotate.y + (pT1->mRotate.y - pT0->mRotate.y) * mFrame;
        it->mParameter.mRotate.z = pT0->mRotate.z + (pT1->mRotate.z - pT0->mRotate.z) * mFrame;

        it->mParameter.mTranslate.x = pT0->mTranslate.x + (pT1->mTranslate.x - pT0->mTranslate.x) * mFrame;
        it->mParameter.mTranslate.y = pT0->mTranslate.y + (pT1->mTranslate.y - pT0->mTranslate.y) * mFrame;
        it->mParameter.mTranslate.z = pT0->mTranslate.z + (pT1->mTranslate.z - pT0->mTranslate.z) * mFrame;

        it->mParameter.mScale.x = pT0->mScale.x + (pT1->mScale.x - pT0->mScale.x) * mFrame;
        it->mParameter.mScale.y = pT0->mScale.y + (pT1->mScale.y - pT0->mScale.y) * mFrame;
        it->mParameter.mScale.z = pT0->mScale.z + (pT1->mScale.z - pT0->mScale.z) * mFrame;
        // clang-format on

        it->SetMtxDirty();
    }

    RP_NW4R_LIST_FOREACH (nw4r::ef::Particle, it, *pListParticle) {
        const nw4r::ef::ParticleParameter* pT0 =
            &pLoadParticle[it->GetObjectIdx()];

        const nw4r::ef::ParticleParameter* pT1 =
            &pSaveParticle[it->GetObjectIdx()];

        if (it->mTick <= 1) {
            continue;
        }

        // clang-format off
        it->mParameter.mScale.x = pT0->mScale.x + (pT1->mScale.x - pT0->mScale.x) * mFrame;
        it->mParameter.mScale.y = pT0->mScale.y + (pT1->mScale.y - pT0->mScale.y) * mFrame;

        it->mParameter.mRotate.x = pT0->mRotate.x + (pT1->mRotate.x - pT0->mRotate.x) * mFrame;
        it->mParameter.mRotate.y = pT0->mRotate.y + (pT1->mRotate.y - pT0->mRotate.y) * mFrame;
        it->mParameter.mRotate.z = pT0->mRotate.z + (pT1->mRotate.z - pT0->mRotate.z) * mFrame;

        for (int i = 0; i < nw4r::ef::TEX_LAYER_MAX; i++) {
            it->mParameter.mTextureScale[i].x = pT0->mTextureScale[i].x + (pT1->mTextureScale[i].x - pT0->mTextureScale[i].x) * mFrame;
            it->mParameter.mTextureScale[i].y = pT0->mTextureScale[i].y + (pT1->mTextureScale[i].y - pT0->mTextureScale[i].y) * mFrame;

            it->mParameter.mTextureRotate[i] = pT0->mTextureRotate[i] + (pT1->mTextureRotate[i] - pT0->mTextureRotate[i]) * mFrame;

            it->mParameter.mTextureTranslate[i].x = pT0->mTextureTranslate[i].x + (pT1->mTextureTranslate[i].x - pT0->mTextureTranslate[i].x) * mFrame;
            it->mParameter.mTextureTranslate[i].y = pT0->mTextureTranslate[i].y + (pT1->mTextureTranslate[i].y - pT0->mTextureTranslate[i].y) * mFrame;
        }

        it->mParameter.mVelocity.x = pT0->mVelocity.x + (pT1->mVelocity.x - pT0->mVelocity.x) * mFrame;
        it->mParameter.mVelocity.y = pT0->mVelocity.y + (pT1->mVelocity.y - pT0->mVelocity.y) * mFrame;
        it->mParameter.mVelocity.z = pT0->mVelocity.z + (pT1->mVelocity.z - pT0->mVelocity.z) * mFrame;

        it->mParameter.mPosition.x = pT0->mPosition.x + (pT1->mPosition.x - pT0->mPosition.x) * mFrame;
        it->mParameter.mPosition.y = pT0->mPosition.y + (pT1->mPosition.y - pT0->mPosition.y) * mFrame;
        it->mParameter.mPosition.z = pT0->mPosition.z + (pT1->mPosition.z - pT0->mPosition.z) * mFrame;

        for (int i = 0; i < nw4r::ef::COLOR_LAYER_MAX; i++) {
            for (int j = 0; j < nw4r::ef::COLOR_IDX_MAX; j++) {
                it->mParameter.mColor[i][j].r = pT0->mColor[i][j].r + (pT1->mColor[i][j].r - pT0->mColor[i][j].r) * mFrame;
                it->mParameter.mColor[i][j].g = pT0->mColor[i][j].g + (pT1->mColor[i][j].g - pT0->mColor[i][j].g) * mFrame;
                it->mParameter.mColor[i][j].b = pT0->mColor[i][j].b + (pT1->mColor[i][j].b - pT0->mColor[i][j].b) * mFrame;
                it->mParameter.mColor[i][j].a = pT0->mColor[i][j].a + (pT1->mColor[i][j].a - pT0->mColor[i][j].a) * mFrame;
            }
        }

        it->mParameter.mMomentum = pT0->mMomentum + (pT1->mMomentum - pT0->mMomentum) * mFrame;
        // clang-format on
    }

    mFrame += mFrameRate;

    if (mFrame >= 1.0f) {
        mIsSlowEffect = true;
        mBackSaveBuffer ^= 1;
        mFrame -= 1.0f;
    } else {
        mIsSlowEffect = false;
    }
}
