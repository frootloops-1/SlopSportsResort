#include <Pack/RPKernel/RPSysEffectBase.h>
#include <Pack/RPKernel/RPSysEffectMgr.h>

#include <nw4r/ef.h>
#include <nw4r/math.h>

#include <cstring>

/**
 * @brief Dummy effect handle
 */
const nw4r::ef::Handle<nw4r::ef::Effect> RPSysEffect::INVALID_HANDLE;

/**
 * @brief Constructor
 *
 * @param pName Effect name
 * @param drawGroup Effect draw group
 */
RPSysEffect::RPSysEffect(const char* pName, u32 drawGroup) {
    std::strncpy(mName, pName, NAME_LENGTH);

    mDrawGroup = drawGroup;
    mDrawScene = 0;

    reset();
}

/**
 * @brief Constructor
 *
 * @param pName Effect name
 * @param drawGroup Effect draw group
 * @param drawScene Effect draw scene
 */
RPSysEffect::RPSysEffect(const char* pName, u32 drawGroup, u32 drawScene) {
    std::strncpy(mName, pName, NAME_LENGTH);

    mDrawGroup = drawGroup;
    mDrawScene = drawScene;

    reset();
}

/**
 * @brief Destructor
 */
RPSysEffect::~RPSysEffect() {}

/**
 * @brief Creates this effect if it is not alive
 *
 * @return Success
 */
bool RPSysEffect::create() {
    if (isValid() && isAlive()) {
        return false;
    }

    reset();

    mHandle = RP_GET_INSTANCE(RPSysEffectMgr)
                  ->createEffect(mName, mDrawGroup, mDrawScene);

    return isValid();
}

/**
 * @brief Fades away and destroys this effect
 */
void RPSysEffect::fade() {
    if (isValid()) {
        mHandle.GetPtr()->RetireEmitterAll();
        mHandle = INVALID_HANDLE;
    }
}

/**
 * @brief Fades away this effect without destroying the handle
 */
void RPSysEffect::followFade() {
    if (isValid()) {
        mHandle.GetPtr()->RetireEmitterAll();
    }
}

/**
 * @brief Destroys this effect and all of its particles
 */
void RPSysEffect::forceKill() {
    if (isValid()) {
        mHandle.GetPtr()->RetireEmitterAll();
        mHandle.GetPtr()->RetireParticleAll();
        mHandle = INVALID_HANDLE;
    }
}

/**
 * @brief Toggles whether this effect will update
 *
 * @param disable Whether to disable updating
 */
void RPSysEffect::setDisableCalc(bool disable) {
    if (isValid()) {
        mHandle.GetPtr()->SetFlagDisableCalc(disable);
    }
}

/**
 * @brief Toggles whether this effect will draw
 *
 * @param disable Whether to disable drawing
 */
void RPSysEffect::setDisableDraw(bool disable) {
    if (isValid()) {
        mHandle.GetPtr()->SetFlagDisableDraw(disable);
    }
}

/**
 * @brief Toggles whether this effect will update and draw
 *
 * @param disable Whether to disable both updating and drawing
 */
void RPSysEffect::setDisableCalcDraw(bool disable) {
    if (isValid()) {
        mHandle.GetPtr()->SetFlagDisableCalc(disable);
        mHandle.GetPtr()->SetFlagDisableDraw(disable);
    }
}

void RPSysEffect::setLife(u16 life, u32 mode) {
    mUnk80.fn_8024B904(life, mode);
}

void RPSysEffect::setEmitRatio(f32 ratio, u32 mode) {
    mUnk80.fn_8024B8B8(ratio, mode);
}

void RPSysEffect::setEmitInterval(u16 interval, u32 mode) {
    mUnk80.fn_8024B878(interval, mode);
}

void RPSysEffect::setEmitEmitDiv(u16 emitDiv, u32 mode) {
    mUnk80.fn_8024B838(emitDiv, mode);
}

void RPSysEffect::setPowerRadiationDir(f32 power, u32 mode) {
    mUnk80.fn_8024B7D8(power, mode);
}

void RPSysEffect::setPowerSpecDir(f32 power, u32 mode) {
    mUnk80.fn_8024B78C(power, mode);
}

/**
 * @brief Sets this effect's velocity
 *
 * @param rVelocity Velocity
 */
void RPSysEffect::setVelocity(const nw4r::math::VEC3& rVelocity) {
    if (isValid()) {
        mHandle.GetPtr()->SetVelocity(rVelocity);
    }
}

void RPSysEffect::setColor(u8 r, u8 g, u8 b, u8 a, u32 mode) {
    GXColor color = {r, g, b, a};
    mUnk80.fn_8024B720(color, mode);
    mFlags.setBit(EFlag_ColorDirty);
}

void RPSysEffect::setColor(u8 r, u8 g, u8 b, u32 mode) {
    GXColor color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = 255;
    mUnk80.fn_8024B720(color, mode);
    mFlags.setBit(EFlag_ColorDirty);
}

void RPSysEffect::setColor(u8 a, u32 mode) {
    GXColor color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = a;
    mUnk80.fn_8024B720(color, mode);
    mFlags.setBit(EFlag_ColorDirty);
}

void RPSysEffect::fn_8023E52C(const GXColor& rColor0, const GXColor& rColor1,
                              int idx, u32 mode) {
    mUnk80.fn_8024B68C(rColor0, rColor1, idx, mode);
}

void RPSysEffect::fn_8023E524(u8 arg0, u8 arg1, int idx, u32 mode) {
    mUnk80.fn_8024B61C(arg0, arg1, idx, mode);
}

void RPSysEffect::fn_8023E51C(const nw4r::math::VEC2& rVec, u32 mode) {
    mUnk80.fn_8024B5C8(rVec, mode);
}

void RPSysEffect::fn_8023E514(const nw4r::math::VEC2& rVec, u32 mode) {
    mUnk80.fn_8024B574(rVec, mode);
}

void RPSysEffect::fn_8023E50C(const nw4r::math::VEC3& rVec, bool enable,
                              u32 mode) {
    mUnk80.fn_8024B4E8(rVec, enable, mode);
}

void RPSysEffect::fn_8023E504(const nw4r::math::VEC3& rVec, u32 mode) {
    mUnk80.fn_8024B48C(rVec, mode);
}

/**
 * @brief Sets this effect's scale
 *
 * @param scale Effect scale (uniform)
 */
void RPSysEffect::setScale(f32 scale) {
    mFlags.setBit(EFlag_ScaleDirty);
    mScale.x = scale;
    mScale.y = scale;
    mScale.z = scale;
}

/**
 * @brief Sets this effect's scale
 *
 * @param rScale Effect scale
 */
void RPSysEffect::setScale(const nw4r::math::VEC3& rScale) {
    mFlags.setBit(EFlag_ScaleDirty);
    mScale = rScale;
}

/**
 * @brief Sets this effect's position
 *
 * @param rPosition Effect position
 */
void RPSysEffect::setPos(const nw4r::math::VEC3& rPosition) {
    mFlags.setBit(EFlag_PositionDirty);
    mPosition = rPosition;
}

/**
 * @brief Sets this effect's transformation matrix
 *
 * @param rTransform Effect transformation matrix
 */
void RPSysEffect::setMtx(const nw4r::math::MTX34& rTransform) {
    mFlags.setBit(EFlag_TransformDirty);
    nw4r::math::MTX34Copy(&mTransform, &rTransform);
}

void RPSysEffect::fn_8023E428(int arg) {
    if (isValid()) {
        Unk_806B98E0* pEffect = getEffect();
        pEffect->fn_8024AA70(arg, mFlags.onBit(EFlag_Updated));
    }
}

/**
 * @brief Flushes this effect's configuration
 */
void RPSysEffect::update() {
    if (isValid()) {
        if (isAlive()) {
            Unk_806B98E0* pEffect = getEffect();
            nw4r::math::MTX34 mtx;

            if (mFlags.onBit(EFlag_TransformDirty)) {
                nw4r::math::MTX34Copy(&mtx, &mTransform);
            } else {
                nw4r::math::MTX34Identity(&mtx);
            }

            if (mFlags.onBit(EFlag_ScaleDirty)) {
                mtx._00 *= mScale.x;
                mtx._10 *= mScale.x;
                mtx._20 *= mScale.x;

                mtx._01 *= mScale.y;
                mtx._11 *= mScale.y;
                mtx._21 *= mScale.y;

                mtx._02 *= mScale.z;
                mtx._12 *= mScale.z;
                mtx._22 *= mScale.z;
            }

            if (mFlags.onBit(EFlag_PositionDirty)) {
                mtx._03 = mPosition.x;
                mtx._13 = mPosition.y;
                mtx._23 = mPosition.z;
            }

            pEffect->SetRootMtx(mtx);

            if (mFlags.onBit(EFlag_ColorDirty)) {
                pEffect->fn_8024AAE8();
            }

            mFlags.setBit(EFlag_Updated);
            pEffect->fn_8024AFDC(&mUnk80);
        } else {
            mHandle = INVALID_HANDLE;
        }
    }
}

u16 RPSysEffect::fn_8023E240() const {
    if (isValid()) {
        return mHandle.GetPtr()->GetNumEmitter();
    }

    return 0;
}

/**
 * @brief Clears this effect's configuration
 */
void RPSysEffect::reset() {
    mFlags.makeAllZero();

    mScale.x = 1.0f;
    mScale.y = 1.0f;
    mScale.z = 1.0f;

    mPosition.x = 0.0f;
    mPosition.y = 0.0f;
    mPosition.z = 0.0f;

    nw4r::math::MTX34Identity(&mTransform);

    mHandle = INVALID_HANDLE;
    mUnk80.fn_8024B3AC();
}
