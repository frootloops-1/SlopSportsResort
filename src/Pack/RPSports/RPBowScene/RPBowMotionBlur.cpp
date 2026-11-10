// Resort (RZTE01_01) port of Wii Sports RPBowMotionBlur.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

#include <Pack/RPSports/RPBowScene/bowling.h>

extern "C" void* sCurrentHeap__Q23EGG4Heap;  // EGG::Heap::sCurrentHeap (private)
extern "C" void fn_802BA4DC(void* pSnd, const nw4r::math::VEC3* pos);
extern "C" void* __nw__FUl(unsigned long);
extern "C" void* fn_802BA8D8(void* pObj, void* pHeap, int align);

namespace Bowling {

// Appears to check frustum culling
extern "C" bool fn_80372C18(void* pCullingCtx, const nw4r::math::VEC3* pos, f32 radius);

extern "C" void fn_804D27B4() {}

/**
 * @brief Destructor
 */
// MATCH-PENDING (R17): ledger #9. Hand-written mangled dtor; real source is a class dtor (base dtors trivial in Resort).
extern "C" void* __dt__Q27Bowling15RPBowMotionBlurFv(void* pThis, s32 deleteFlag) {
    if (pThis != NULL && deleteFlag > 0) {
        operator delete(pThis);
    }
    return pThis;
}

/**
 * @brief Sets the models used for the motion blur effect
 *
 * @param pReal1 Real model 1
 * @param pReal2 Real model 2
 * @param pReal3 Real model 3
 * @param pRefl1 Reflection model 1
 * @param pRefl2 Reflection model 2
 * @param pRefl3 Reflection model 3
 */
void RPBowMotionBlur::SetBlurModels(RPGrpModel* pReal1, RPGrpModel* pReal2, RPGrpModel* pReal3, RPGrpModel* pRefl1, RPGrpModel* pRefl2, RPGrpModel* pRefl3) {
    models[0].pRealModel = pReal1;
    models[0].pReflectionModel = pRefl1;
    models[1].pRealModel = pReal2;
    models[1].pReflectionModel = pRefl2;
    models[2].pRealModel = pReal3;
    models[2].pReflectionModel = pRefl3;
    void* pSnd = __nw__FUl(0xD4);
    if (pSnd) {
        pSnd = fn_802BA8D8(pSnd, sCurrentHeap__Q23EGG4Heap, 2);
    }
    this->pSnd = pSnd;
}

/**
 * @brief Deactivates the motion blur effect
 */
void RPBowMotionBlur::DeactivateBlur() {
    isActive = false;
}

/**
 * @brief Updates the transform matrices for the motion blur
 *
 * @param pBaseMtx Base transform matrix
 * @param blurSpeed Speed of the blur effect
 */
void RPBowMotionBlur::UpdateBlurTransform(const nw4r::math::MTX34* pBaseMtx, f32 blurSpeed) {
    if (blurSpeed > 0.001f) {
        isActive = true;
    } else {
        isActive = false;
        return;
    }

    blurMtxs[2] = *pBaseMtx;
    blurMtxs[1] = blurMtxs[2];
    blurMtxs[0] = blurMtxs[1];

    f32 stretchFactor = (blurSpeed * 2.0f) / 5.267f;
    blurMtxs[0]._03 -= pBaseMtx->_00 * blurSpeed;
    blurMtxs[0]._13 -= pBaseMtx->_10 * blurSpeed;
    blurMtxs[0]._23 -= pBaseMtx->_20 * blurSpeed;

    blurMtxs[2]._03 += pBaseMtx->_00 * blurSpeed;
    blurMtxs[2]._13 += pBaseMtx->_10 * blurSpeed;
    blurMtxs[2]._23 += pBaseMtx->_20 * blurSpeed;

    blurMtxs[1]._00 *= stretchFactor;
    blurMtxs[1]._10 *= stretchFactor;
    blurMtxs[1]._20 *= stretchFactor;

    speed = blurSpeed;

    nw4r::math::VEC3 pos(pBaseMtx->_03, pBaseMtx->_13, pBaseMtx->_23);
    fn_802BA4DC(pSnd, &pos);
}

/**
 * @brief Renders the motion blur models
 *
 * @param pCullingCtx Frustum culling context
 */
void RPBowMotionBlur::DrawBlur(void* pCullingCtx) {
    if (!isActive) {
        return;
    }

    nw4r::math::VEC3 pos(blurMtxs[1]._03, blurMtxs[1]._13, blurMtxs[1]._23);
    if (!fn_80372C18(pCullingCtx, &pos, speed * 2.0f)) {
        return;
    }

    nw4r::math::MTX34* pBlurMtx;
    for (int i = 0; i < 3; i++) {
        pBlurMtx = &blurMtxs[i];
        models[i].pRealModel->Unk_801E5D00(pBlurMtx);
        models[i].pRealModel->Calc();
        models[i].pRealModel->Entry();

        nw4r::math::MTX34 reflectionMtx = *pBlurMtx;
        reflectionMtx._10 *= -1.0f;
        reflectionMtx._11 *= -1.0f;
        reflectionMtx._12 *= -1.0f;
        reflectionMtx._13 *= -1.0f;

        models[i].pReflectionModel->Unk_801E5D00(&reflectionMtx);
        models[i].pReflectionModel->Calc();
        models[i].pReflectionModel->Entry();
    }
}

} // namespace Bowling

// RPBowMotionBlur vtable (slot 0 = RTTI, slot 1 = this-offset). The class in
// bowling.h only declares the virtual dtor, so the full table (8031641C stores
// it in its inline ctor) is written out as data under its address label.
extern "C" {
void* __dt__Q27Bowling15RPBowMotionBlurFv(void*, s32);
void DeactivateBlur__Q27Bowling15RPBowMotionBlurFv();
void DrawBlur__Q27Bowling15RPBowMotionBlurFPv();
void fn_804D3574();
void ogws_fn_80316418();
void fn_804C7D14();
void fn_804C7D10();

void* lbl_803CA940[] = {
    0,
    0,
    (void*)__dt__Q27Bowling15RPBowMotionBlurFv,
    (void*)DeactivateBlur__Q27Bowling15RPBowMotionBlurFv,
    (void*)DrawBlur__Q27Bowling15RPBowMotionBlurFPv,
    (void*)fn_804D3574,
    (void*)ogws_fn_80316418,
    (void*)fn_804C7D14,
    (void*)fn_804C7D10,
};
}  // extern "C"
