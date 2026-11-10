// Resort (RZTE01_01) port of Wii Sports RPBowActiveBall.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

// g3d_gpu.h (`static const u8 cm2hw[]`) emits a stray .sdata2 entry that this
// object lacks. Pre-define its include guard so it is skipped; nothing here uses it.
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPSports/RPBowScene/bowling.h>

extern "C" {
// Returns the model's material color
GXColor fn_8037307C(RPGrpModel* pModel, int unk1, int unk2);

// Applies the given color to the model
void fn_80372FD8(RPGrpModel* pModel, int unk1, int unk2, GXColor color);
}

extern "C" {
void fn_8024E34C(RPGrpModel* pModel, u32 flags);

// Emitted in reverse source order, so these land after RenderModelSet/ResetRenderState.
void fn_804D11D4() {}

Bowling::RPBowActiveBall* fn_804D1194(Bowling::RPBowActiveBall* pThis, s32 deleteFlag) {
    if (pThis != NULL && deleteFlag > 0) {
        operator delete(pThis);
    }
    return pThis;
}

void fn_804D1190() {}

void fn_804D1174(Bowling::RPBowActiveBall* pThis, int idx, RPGrpModel* pReal, RPGrpModel* pRefl) {
    pThis->models[idx].pRealModel = pReal;
    pThis->models[idx].pReflectionModel = pRefl;
    fn_8024E34C(pReal, 1);  // RPGrpModel::CreateBoundingInfo (name not in this unit's symbols)
}
}

namespace Bowling {

/**
 * @brief Initializes the render object to its default state
 */
void RPBowActiveBall::ResetRenderState() {
    MTX34Identity(&mtx);

    field_0x74 = 0.0f;
    index = 0;

    mtx._23 = 9999.0f;
    alpha = 1.0f;
}

/**
 * @brief Renders the currently selected model set
 *
 * Updates the main model's transform and color, renders a mirrored version used
 * for reflections, and optionally submits the model to the shadow texture renderer.
 */
void RPBowActiveBall::RenderModelSet() {
    if (mtx._23 > 49.0f) {
        return;
    }

    nw4r::math::MTX34 worldMtx = mtx;

    f32 scale = 1.0f;
    worldMtx._00 *= scale;
    worldMtx._01 *= scale;
    worldMtx._02 *= scale;

    worldMtx._10 *= scale;
    worldMtx._11 *= scale;
    worldMtx._12 *= scale;

    worldMtx._20 *= scale;
    worldMtx._21 *= scale;
    worldMtx._22 *= scale;

    GXColor color = fn_8037307C(models[index].pRealModel, 0, 0);
    color.a = (s8) (255.0f * alpha);

    fn_80372FD8(models[index].pRealModel, 0, 0, color);

    models[index].pRealModel->Unk_801E5D00(&worldMtx);

    models[index].pRealModel->UpdateFrame();
    models[index].pRealModel->Calc();
    models[index].pRealModel->Entry();

    nw4r::math::MTX34 reflectionMtx = worldMtx;

    reflectionMtx._10 *= -1.0f;
    reflectionMtx._11 *= -1.0f;
    reflectionMtx._12 *= -1.0f;
    reflectionMtx._13 *= -1.0f;

    nw4r::math::VEC3 src(0.0f, 0.0f, 0.0f);
    nw4r::math::VEC3 dst;

    f32 limit = 1.075f;
    f32 thresholdZ = -192.0f + limit;
    f32 thresholdY = -limit;
    f32 offset = 0.0f;

    VEC3Transform(&dst, &reflectionMtx, &src);

    if (dst.y > thresholdY && dst.z > thresholdZ) {
        f32 diff = thresholdY - dst.y;

        if (offset > diff) {
            offset = diff;
        }
    }

    reflectionMtx._13 += offset;

    models[index].pReflectionModel->Unk_801E5D00(&reflectionMtx);

    models[index].pReflectionModel->UpdateFrame();
    models[index].pReflectionModel->Calc();
    models[index].pReflectionModel->Entry();

    if (!disableShadow) {
        pShadowTexture->AddModel(models[index].pRealModel, 1.0f);
    }
}

} // namespace Bowling

extern "C" void fn_804D0E34() {}

// Vtable of Bowling::RPBowActiveBall (stored by the RPBow_8031641C ctor), written as a
// data table under its address label: the class is not modelled with its virtual list yet.
extern "C" {
void ResetRenderState__Q27Bowling15RPBowActiveBallFv();
void RenderModelSet__Q27Bowling15RPBowActiveBallFv();
void fn_804C7B60();
void fn_804C7D14();
void fn_804C7D10();

void* lbl_806DEAD0[10] = {
    0,
    0,
    (void*)fn_804D1194,
    (void*)ResetRenderState__Q27Bowling15RPBowActiveBallFv,
    (void*)RenderModelSet__Q27Bowling15RPBowActiveBallFv,
    (void*)fn_804D0E34,
    (void*)fn_804C7B60,
    (void*)fn_804C7D14,
    (void*)fn_804C7D10,
    0,
};
}  // extern "C"
