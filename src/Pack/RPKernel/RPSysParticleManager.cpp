#include <Pack/RPKernel/RPSysParticleManager.h>

#include <Pack/RPKernel/RPSysEffectMemoryManager.h>

/**
 * Resort emits this file's functions in reverse source order: the last
 * definition here is the first function in .text (0x80243BD4).
 */

inline BOOL RPSysParticleManager::isChildParam() const {
    return mManagerEM->mParent != NULL || mResource != mManagerEM->mResource;
}

/**
 * @brief Constructor
 */
RPSysParticleManager::RPSysParticleManager() {
    reset();
}

/**
 * @brief Destructor
 */
RPSysParticleManager::~RPSysParticleManager() {}

/**
 * @brief Prepares this particle manager for creation
 *
 * @param pParent Parent emitter
 * @param pResource Emitter resource data
 * @return Success
 */
bool RPSysParticleManager::Initialize(nw4r::ef::Emitter* pParent,
                                      nw4r::ef::EmitterResource* pResource) {
    reset();
    mpParam = static_cast<Unk_806B94B8*>(pParent)->fn_80244758();

    return nw4r::ef::ParticleManager::Initialize(pParent, pResource);
}

/**
 * @brief Creates a new particle, applying the parameter overrides
 */
nw4r::ef::Particle* RPSysParticleManager::CreateParticle(
    u16 life, nw4r::math::VEC3 pos, nw4r::math::VEC3 vel,
    const nw4r::math::MTX34* pSpace, f32 momentum,
    const nw4r::ef::EmitterInheritSetting* pSetting,
    nw4r::ef::Particle* pReferencePtcl, u16 calcRemain) {

    nw4r::ef::Particle* pPtcl = nw4r::ef::ParticleManager::CreateParticle(
        life, pos, vel, pSpace, momentum, pSetting, pReferencePtcl,
        calcRemain);

    if (pPtcl != NULL && mpParam != NULL && mpParam->isAnyEnable()) {
        bool child = isChildParam();

        if (mpParam->isEnable(child, 0x1)) {
            pPtcl->mLife = mpParam->fn_8024B93C();
        }

        nw4r::ef::ParticleParameter* pParam = pPtcl->GetParticleParameter();
        if (pParam != NULL) {
            if (mpParam->isEnable(child, 0x2000)) {
                GXColor* pColor0 = mpParam->fn_8024B708(0, 0);
                GXColor* pColor1 = mpParam->fn_8024B708(1, 0);

                pParam->mColor[0][0].r = pColor0->r;
                pParam->mColor[0][0].g = pColor0->g;
                pParam->mColor[0][0].b = pColor0->b;
                pParam->mColor[0][1].r = pColor1->r;
                pParam->mColor[0][1].g = pColor1->g;
                pParam->mColor[0][1].b = pColor1->b;
            }

            if (mpParam->isEnable(child, 0x4000)) {
                GXColor* pColor0 = mpParam->fn_8024B708(0, 1);
                GXColor* pColor1 = mpParam->fn_8024B708(1, 1);

                pParam->mColor[1][0].r = pColor0->r;
                pParam->mColor[1][0].g = pColor0->g;
                pParam->mColor[1][0].b = pColor0->b;
                pParam->mColor[1][1].r = pColor1->r;
                pParam->mColor[1][1].g = pColor1->g;
                pParam->mColor[1][1].b = pColor1->b;
            }

            if (mpParam->isEnable(child, 0x8000)) {
                pParam->mColor[0][0].a = mpParam->fn_8024B674(0, 0);
                pParam->mColor[0][1].a = mpParam->fn_8024B674(1, 0);
            }

            if (mpParam->isEnable(child, 0x10000)) {
                pParam->mColor[1][0].a = mpParam->fn_8024B674(0, 1);
                pParam->mColor[1][1].a = mpParam->fn_8024B674(1, 1);
            }

            if (mpParam->isEnable(child, 0x20000)) {
                pParam->mSize = *mpParam->fn_8024B614();
            }

            if (mpParam->isEnable(child, 0x80000)) {
                pParam->mRotate = *mpParam->fn_8024B56C();
            }
        }
    }

    return pPtcl;
}

/**
 * @brief Applies the manager-level overrides, then updates the particles
 */
void RPSysParticleManager::Calc() {
    if (mpParam != NULL && mpParam->isAnyEnable()) {
        bool child = isChildParam();

        if (mpParam->isEnable(child, 0x1000)) {
            mModifier.mLight.mType = 1;
            mModifier.mLight.mAmbient = *mpParam->fn_8024B774();
        }

        if (mpParam->isEnable(child, 0x40000)) {
            Modifier_SetScale(*mpParam->fn_8024B5C0());
        }

        if (mpParam->isEnable(child, 0x100000)) {
            Modifier_SetRotate(*mpParam->fn_8024B564());
        }
    }

    nw4r::ef::ParticleManager::Calc();
}
