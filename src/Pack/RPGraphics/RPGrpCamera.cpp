#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

#include <cmath>


/**
 * @brief Default camera
 */
RPGrpCamera RPGrpCamera::sDefaultCamera;

/**
 * @brief Initializes the camera system
 */
void RPGrpCamera::Initialize() {}

/**
 * @brief Constructor
 */
RPGrpCamera::RPGrpCamera() : mCameraType(ECameraType_LookAt) {
    mFlags.all = 0;
    Identity();
}

/**
 * @brief Copies the state from another camera
 *
 * @param rOther Camera from which to copy
 */
void RPGrpCamera::CopyFromAnother(const RPGrpCamera& rOther) {
    if (this == &rOther) {
        return;
    }

    nw4r::math::MTX34Copy(&mViewMtx, &rOther.mViewMtx);
    nw4r::math::MTX34Copy(&mWorldMtx, &rOther.mWorldMtx);
    nw4r::math::MTX34Copy(&mAnmViewMtx, &rOther.mAnmViewMtx);
    nw4r::math::MTX34Copy(&mDirectWorldMtx, &rOther.mDirectWorldMtx);
    nw4r::math::MTX34Copy(&mWorldMtxOld, &rOther.mWorldMtxOld);
    nw4r::math::MTX34Copy(&mSavedViewMtx, &rOther.mSavedViewMtx);

    mPosition = rOther.mPosition;
    mTarget = rOther.mTarget;
    mRotation = rOther.mRotation;

    mDistance = rOther.mDistance;
    mRight = rOther.mRight;
    mUp = rOther.mUp;
    mForward = rOther.mForward;

    mCameraType = rOther.mCameraType;
    mFlags.all = rOther.mFlags.all & ~0x20E;
}

/**
 * @brief Copies this camera's state to another camera
 *
 * @param rDst Camera to copy to
 */
void RPGrpCamera::Unk_8024D0E4(RPGrpCamera& rDst) const {
    rDst.CopyFromAnother(*this);
}

/**
 * @brief Resets the camera transformation
 */
void RPGrpCamera::Identity() {
    nw4r::math::MTX34Identity(&mViewMtx);
    nw4r::math::MTX34Identity(&mWorldMtxOld);
    nw4r::math::MTX34Identity(&mSavedViewMtx);

    mRotation.x = mRotation.y = mRotation.z = 0.0f;

    mPosition.x = mPosition.y = mPosition.z = 0.0f;

    mTarget.x = mTarget.y = 0.0f;
    mTarget.z = -1.0f;

    mDistance = -1.0f;

    mUp.x = mUp.z = 0.0f;
    mUp.y = 1.0f;

    CalcMatrix();
    mFlags.bits.mUnk20 = 0;
}

/**
 * @brief Updates the camera state based on the camera type
 */
void RPGrpCamera::CalcMatrix() {
    nw4r::math::MTX34Copy(&mWorldMtxOld, &mWorldMtx);

    switch (mCameraType) {
    case ECameraType_Anm: {
        nw4r::math::MTX34Copy(&mViewMtx, &mAnmViewMtx);
        SyncFromMatrix(ESyncFlag_ForAnmCamera);
        break;
    }

    case ECameraType_Direct: {
        nw4r::math::MTX34Copy(&mWorldMtx, &mDirectWorldMtx);
        SyncFromMatrix(ESyncFlag_ForDirectCamera);
        break;
    }

    case ECameraType_LookAt: {
        nw4r::math::MTX34LookAt(&mViewMtx, &mPosition, &mUp, &mTarget);

        f32 length = nw4r::math::VEC3DistSq(&mPosition, &mTarget);
        mDistance = -nw4r::math::FSqrt(length);

        SyncFromMatrix(ESyncFlag_ForLookAtCamera);
        break;
    }

    case ECameraType_Orbit: {
        nw4r::math::MTX34 rot;
        PSMTXTrans(mViewMtx, -mTarget.x, -mTarget.y, -mTarget.z);

        PSMTXRotRad(rot, 'Y', NW4R_MATH_DEG_TO_RAD(-mRotation.y));
        nw4r::math::MTX34Mult(&mViewMtx, &rot, &mViewMtx);

        PSMTXRotRad(rot, 'X', NW4R_MATH_DEG_TO_RAD(-mRotation.x));
        nw4r::math::MTX34Mult(&mViewMtx, &rot, &mViewMtx);

        PSMTXRotRad(rot, 'Z', NW4R_MATH_DEG_TO_RAD(-mRotation.z));
        nw4r::math::MTX34Mult(&mViewMtx, &rot, &mViewMtx);

        mViewMtx._23 += mDistance;

        SyncFromMatrix(ESyncFlag_ForOrbitCamera);
        break;
    }

    case ECameraType_Free: {
        nw4r::math::MTX34 rot;
        PSMTXRotRad(mWorldMtx, 'Z', NW4R_MATH_DEG_TO_RAD(mRotation.z));

        PSMTXRotRad(rot, 'X', NW4R_MATH_DEG_TO_RAD(mRotation.x));
        nw4r::math::MTX34Mult(&mWorldMtx, &rot, &mWorldMtx);

        PSMTXRotRad(rot, 'Y', NW4R_MATH_DEG_TO_RAD(mRotation.y));
        nw4r::math::MTX34Mult(&mWorldMtx, &rot, &mWorldMtx);

        PSMTXTransApply(mWorldMtx, mWorldMtx, mPosition.x, mPosition.y,
                        mPosition.z);

        SyncFromMatrix(ESyncFlag_ForFreeCamera);
        break;
    }
    }

    mRight.x = mWorldMtx._00;
    mRight.y = mWorldMtx._10;
    mRight.z = mWorldMtx._20;

    mForward.x = mWorldMtx._02;
    mForward.y = mWorldMtx._12;
    mForward.z = mWorldMtx._22;

    mFlags.bits.mUnk80 = 0;
}

/**
 * @brief Saves the current state of the view matrix
 */
void RPGrpCamera::SaveCameraMatrix() {
    nw4r::math::MTX34Copy(&mSavedViewMtx, &mViewMtx);
}

/**
 * @brief Interpolates the camera matrix between the previous and current
 * world matrices
 */
// MATCH-PENDING (R17): volatile flag reads force the reload of mFlags
void RPGrpCamera::Unk_8024CC84() {
    if (*(volatile u16*)&mFlags.all & 0x100) {
        if (!(*(volatile u16*)&mFlags.all & 0x80)) {
            f32 t = RPSysSystem::instance()->Unk_80237918();
            mFlags.all |= 0x80;

            if (t != 1.0f && (mFlags.all & 0x20)) {
                nw4r::math::MTX34* pOld = &mWorldMtxOld;
                nw4r::math::MTX34* pCur = &mWorldMtx;
                nw4r::math::QUAT q0, q1, q;
                nw4r::math::MTX34ToQUAT(&q0, pOld);
                nw4r::math::MTX34ToQUAT(&q1, pCur);
                nw4r::math::C_QUATSlerp(&q, &q0, &q1, t);

                nw4r::math::QUATToMTX34(&mSavedViewMtx, &q);
                mSavedViewMtx._03 = t * (pCur->_03 - pOld->_03) + pOld->_03;
                mSavedViewMtx._13 = t * (pCur->_13 - pOld->_13) + pOld->_13;
                mSavedViewMtx._23 = t * (pCur->_23 - pOld->_23) + pOld->_23;
                nw4r::math::MTX34Inv(&mSavedViewMtx, &mSavedViewMtx);
            } else {
                nw4r::math::MTX34Copy(&mSavedViewMtx, &mViewMtx);
            }

            nw4r::math::MTX34Copy(&mWorldMtxOld, &mWorldMtx);
            mFlags.all |= 0x20;
        }
    } else {
        nw4r::math::MTX34Copy(&mSavedViewMtx, &mViewMtx);
    }
}

/**
 * @brief Converts a position from world-space to screen-space
 *
 * @param[out] pScreenPos Position in screen-space
 * @param rWorldPos Position in world-space
 * @param pScreen Screen
 */
void RPGrpCamera::GetWorldToScreen(nw4r::math::VEC3* pScreenPos,
                                   const nw4r::math::VEC3& rWorldPos,
                                   const RPGrpScreen* pScreen) const {

    nw4r::math::VEC3TransformCoord(pScreenPos, &mViewMtx, &rWorldPos);
    pScreen->GetViewToScreen(pScreenPos, *pScreenPos);
}

/**
 * @brief Converts a position from screen-space to world-space
 *
 * @param[out] pWorldPos Position in world-space
 * @param rScreenPos Position in screen-space
 * @param pScreen Screen
 */
void RPGrpCamera::GetScreenToWorld(nw4r::math::VEC3* pWorldPos,
                                   const nw4r::math::VEC2& rScreenPos,
                                   const RPGrpScreen* pScreen) const {

    pScreen->GetScreenToView(pWorldPos, rScreenPos);
    nw4r::math::VEC3TransformCoord(pWorldPos, &mWorldMtx, pWorldPos);
}

/**
 * @brief Derives components of the camera state from the world matrix
 *
 * @param flags Flags controlling which components to update
 */
void RPGrpCamera::SyncFromMatrix(u16 flags) {
    if (flags & ESyncFlag_ViewMtx) {
        nw4r::math::MTX34Inv(&mViewMtx, &mWorldMtx);
    } else if (flags & ESyncFlag_WorldMtx) {
        nw4r::math::MTX34Inv(&mWorldMtx, &mViewMtx);
    }

    if (flags & ESyncFlag_AnmViewMtx) {
        nw4r::math::MTX34Copy(&mAnmViewMtx, &mViewMtx);
    }

    if (flags & ESyncFlag_DirectWorldMtx) {
        nw4r::math::MTX34Copy(&mDirectWorldMtx, &mWorldMtx);
    }

    if (flags & ESyncFlag_Position) {
        mPosition.x = mWorldMtx._03;
        mPosition.y = mWorldMtx._13;
        mPosition.z = mWorldMtx._23;
    }

    if (flags & ESyncFlag_Up) {
        mUp.x = mWorldMtx._01;
        mUp.y = mWorldMtx._11;
        mUp.z = mWorldMtx._21;
    }

    if (flags & ESyncFlag_Target) {
        mTarget.x = mDistance * mWorldMtx._02 + mWorldMtx._03;
        mTarget.y = mDistance * mWorldMtx._12 + mWorldMtx._13;
        mTarget.z = mDistance * mWorldMtx._22 + mWorldMtx._23;
    }

    if (flags & ESyncFlag_Rotation) {
        f32 _12 = mWorldMtx._12;

        if (_12 - 1.0f >= -1e-22f) {
            mRotation.x = -90.0f;
            mRotation.y = -nw4r::math::Atan2Deg(mWorldMtx._20, mWorldMtx._00);
            mRotation.z = 0.0f;
            return;

        } else if (_12 + 1.0f <= 1e-22f) {
            mRotation.x = +90.0f;
            mRotation.y = -nw4r::math::Atan2Deg(mWorldMtx._20, mWorldMtx._00);
            mRotation.z = 0.0f;
            return;

        } else {
            mRotation.x = -std::asinf(_12) * 180 / NW4R_MATH_PI;
            mRotation.y = -nw4r::math::Atan2Deg(-mWorldMtx._02, mWorldMtx._22);
            mRotation.z = -nw4r::math::Atan2Deg(-mWorldMtx._10, mWorldMtx._11);
        }
    }
}

/**
 * @brief Applies camera settings from the specified scene resource
 *
 * @param scn Scene resource
 * @param refNumber Camera reference number
 * @param frame Animation frame (defaults to the first frame)
 */
void RPGrpCamera::LoadScnCameraMatrix(const nw4r::g3d::ResAnmScn scn,
                                      u8 refNumber, f32 frame) {
    if (!scn.IsValid()) {
        return;
    }

    const nw4r::g3d::ResAnmCamera cam =
        scn.GetResAnmCameraByRefNumber(refNumber);

    nw4r::g3d::CameraAnmResult result;
    cam.GetAnmResult(&result, frame);

    static nw4r::g3d::CameraData cameraData;
    nw4r::g3d::Camera workCamera(&cameraData);
    workCamera.Init();

    nw4r::g3d::Camera::PostureInfo posture;

    switch (result.flags & nw4r::g3d::CameraAnmResult::FLAG_CAMERA_TYPE_MASK) {
    case nw4r::g3d::CameraAnmResult::CAMERATYPE_ROTATE: {
        posture.tp = nw4r::g3d::Camera::POSTURE_ROTATE;

        posture.cameraRotate = result.rotate.rot;
        break;
    }

    case nw4r::g3d::CameraAnmResult::CAMERATYPE_AIM: {
        posture.tp = nw4r::g3d::Camera::POSTURE_AIM;

        posture.cameraTarget = result.rotate.rot;
        posture.cameraTwist = result.aim.twist;

        nw4r::math::VEC3 dir = posture.cameraTarget - result.pos;
        mDistance = -nw4r::math::VEC3Len(&dir);
        break;
    }
    }

    workCamera.SetPosition(result.pos);
    workCamera.SetPosture(posture);

    // Briefly change camera types so we can apply the G3D result
    ECameraType oldType = mCameraType;
    mCameraType = ECameraType_Anm;
    {
        workCamera.GetCameraMtx(&mAnmViewMtx);
        CalcMatrix();
    }
    mCameraType = oldType;
}

// MATCH-PENDING (R17): dead pool-order seed. Puts 1.0f, -1.0f, 0.0f first in this unit's .sdata2 (Resort's
// order); without it four functions load their constants from shifted slots. The real source probably
// has an early-emitted (last-defined) inline or function that uses these literals first.
static void PoolSeed(f32* p) {
    p[0] = 1.0f;
    p[1] = -1.0f;
    p[2] = 0.0f;
}
