// Resort (RZTE01_01) port of Wii Sports RPBowBackgroundNpcManager.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

#define NW4R_G3D_PLATFORM_GPU_H
#include <Pack/RPSports/RPBowScene/bowling.h>
#include <Pack/RPUtility/RPUtlRandom.h>

#define nullptr 0

extern u8 lbl_806F5958;
extern u32 lbl_806F5978;

extern "C" void fn_8034DD08__Q27Bowling25RPBowBackgroundNpcManagerFv();
#pragma force_active on
__declspec(section ".ctors") static void (*backgroundNpcInit)(void) = fn_8034DD08__Q27Bowling25RPBowBackgroundNpcManagerFv;
#pragma force_active reset

struct NpcHelper;
extern "C" {
NpcHelper* fn_804D2B10(Bowling::NpcIdleState*);
void fn_8024DD14(RPGrpModel*, const nw4r::math::VEC3*);
void fn_802478BC(void*, nw4r::math::MTX34*);
void fn_8024789C(void*, nw4r::math::MTX34*);
void fn_8024787C(void*, nw4r::math::MTX34*);
}

namespace Bowling {

// Forward declarations

void fn_804D338C(NpcIdleState* pIdleState, int param_2, int param_3);
NpcIdleStateSub* fn_804D2CBC(NpcIdleState* pIdleState);

BackgroundNpcConfig gBackgroundNpcParams;

static inline void InterpolateRotation(f32* rotation, f32 target, f32 speed) {
    *rotation = speed * (target - *rotation) + *rotation;
}

class RPGrpModelAccessor : public RPGrpModel {
public:
    static RPGrpModelAnm* GetModelAnm(RPGrpModel* pModel) {
        return pModel->*(&RPGrpModelAccessor::mpModelAnm);
    }

    static void SetScale(RPGrpModel* pModel, const nw4r::math::VEC3& rScale) {
        pModel->*(&RPGrpModelAccessor::mBaseScale) = rScale;
    }
};

/**
 * @brief Unknown stub
 */
extern "C" void* __dt__Q27Bowling25RPBowBackgroundNpcManagerFv(void*, s32);

/**
 * @brief Destructor
 */
// MATCH-PENDING (R17): ledger #9. Hand-written mangled dtor; real source is a class dtor (base dtors trivial in Resort).
extern "C" void* __dt__Q27Bowling25RPBowBackgroundNpcManagerFv(void* pThis, s32 deleteFlag) {
    if (pThis != NULL && deleteFlag > 0) {
        operator delete(pThis);
    }
    return pThis;
}

/**
 * @brief Initializes the background NPC configuration
 *
 * @param index Lane index
 */
void RPBowBackgroundNpcManager::InitializeConfig(int index) {
    mConfigIndex = index;

    gBackgroundNpcParams.laneZPositions[0] = 92.0f;
    gBackgroundNpcParams.laneZPositions[1] = 99.0f;
    gBackgroundNpcParams.laneZPositions[2] = 106.0f;
    gBackgroundNpcParams.laneZPositions[3] = 113.0f;

    gBackgroundNpcParams.basePosY = 3.85f;
    gBackgroundNpcParams.seatedPosY = 2.0f;
    gBackgroundNpcParams.mirroredModelZOffset = 6.5f;
    gBackgroundNpcParams.patrolMinX = -120.0f;
    gBackgroundNpcParams.patrolMaxX = 120.0f;
    gBackgroundNpcParams.minWalkSpeed = 0.07f;
    gBackgroundNpcParams.maxWalkSpeed = 0.25f;

    gBackgroundNpcParams.dormantToPatrolChanceDenom = 200;
    gBackgroundNpcParams.patrolToIdleChanceDenom = 400;
    gBackgroundNpcParams.idleToPatrolChanceDenom = 300;

    gBackgroundNpcParams.turnLerpRate = 0.05f;
    gBackgroundNpcParams.idleCenterZoneX = 70.0f;

    gBackgroundNpcParams.minStateDuration = 120;
}

/**
 * @brief Sets the model groups for the manager
 *
 * @param managerIndex Manager index
 * @param pModelGroup0 First model group
 * @param pModelGroup1 Second model group
 */
void RPBowBackgroundNpcManager::SetModelGroups(int managerIndex, NpcModelGroup* pModelGroup0, NpcModelGroup*) {
    mModelGroups[managerIndex][0] = pModelGroup0;
}

/**
 * @brief Unknown stub
 */
void RPBowBackgroundNpcManager::fn_8034E83C() {
    ;
}



extern "C" void fn_804CFD4C(RPBowBackgroundNpcManager* pMgr, int anim) {
    if (pMgr->mMovement.animationState != anim) {
        pMgr->mMovement.animationState = anim;
        for (int i = 0; i < 2; i++) {
            NpcModelGroup* pGroup = pMgr->mModelGroups[pMgr->mModelGroupSet][i];
            RPGrpModelAnm* pAnimation = RPGrpModelAccessor::GetModelAnm(pGroup->mModelA8);
            pAnimation->StartBlend(RPGrpModelAnm::Anm_Chr, anim, 60.0f, 0.0f);
        }
    }
}

/**
 * @brief Resets the manager state
 */
void RPBowBackgroundNpcManager::Reset() {
    mModelGroupSet = 0;
    mMovement.animationState = -1;
    fn_804CFD4C(this, 0);
    memset(&mMovement, 0, 0x30);
    mMovement.behaviorState = 0;
    mMovement.stateTimer = -1;
    fn_804D338C(&mIdleState, 999, 0);
    unk_0x94 = 0;
    for (int j = 0; j < 600; j++) {
        UpdateMovement(nullptr, nullptr);
    }
    lbl_806F5958 = 0;
}

/**
 * @brief Updates the movement state and calculates position
 *
 * @param pOutPosition[out] Output position
 * @param pOutStateFlag[out] Output state flag
 */
void RPBowBackgroundNpcManager::UpdateMovement(nw4r::math::VEC3* pOutPosition, bool* pOutStateFlag) {
    bool stateFlag = true;
    BackgroundNpcConfig* pConfig = &gBackgroundNpcParams;

    if (mMovement.stateTimer < 0) {
        mMovement.stateTimer = 0;
    }

    nw4r::math::VEC3 localVec(0.0f, 0.0f, 0.0f);

    switch (mMovement.behaviorState) {
        case 0:
        {
            if (RPUtlRandom::getU32(pConfig->dormantToPatrolChanceDenom) == 0) {
                mModelGroupSet = RPUtlRandom::getU32(2);
                if (mModelGroupSet >= 2) {
                    mModelGroupSet = 1;
                }
                mMovement.animationState = -1;
                mMovement.behaviorState = 1;
                mMovement.stateTimer = -1;
            }
            stateFlag = false;
            break;
        }

        case 1:
        {
            if (mMovement.stateTimer == 0) {
                f32 walkSpeed = pConfig->minWalkSpeed + RPUtlRandom::getF32() * (pConfig->maxWalkSpeed - pConfig->minWalkSpeed);
                if (RPUtlRandom::getU32(2) == 0) {
                    walkSpeed *= -1.0f;
                }

                mMovement.velocity.x = walkSpeed;
                mMovement.velocity.y = 0.0f;
                mMovement.velocity.z = 0.0f;

                if (walkSpeed < 0.0f) {
                    mMovement.position.x = pConfig->patrolMaxX;
                } else {
                    mMovement.position.x = pConfig->patrolMinX;
                }

                mMovement.position.y = pConfig->basePosY;
                mMovement.position.z = pConfig->laneZPositions[mConfigIndex];
            }

            fn_804CFD4C(this, 1);

            if (std::fabs(mMovement.position.x) < pConfig->idleCenterZoneX && (int)pConfig->minStateDuration < mMovement.stateTimer) {
                if (RPUtlRandom::getU32(pConfig->patrolToIdleChanceDenom) == 0) {
                    mMovement.behaviorState = 2;
                    mMovement.stateTimer = -1;
                }
            }

            f32 targetAngle;
            if (mMovement.velocity.x < 0.0f) {
                targetAngle = 270.0f;
            } else {
                targetAngle = 90.0f;
            }

            mMovement.rotation.y += pConfig->turnLerpRate * (targetAngle - mMovement.rotation.y);
            mMovement.position += mMovement.velocity;

            if (mMovement.position.x < pConfig->patrolMinX || mMovement.position.x > pConfig->patrolMaxX) {
                mMovement.behaviorState = 0;
                mMovement.stateTimer = -1;
            }
            break;
        }

        case 2:
        {
            if (mMovement.stateTimer == 0) {
                mIdleState.sub.field_0x2C = true;
                mIdleState.sub.unk_0x8 = lbl_806F5978;
            }

            fn_804CFD4C(this, 0);

            NpcIdleStateSub* pRet = fn_804D2CBC(&mIdleState);
            f32 targetRotation = pRet->targetRotation;
            localVec = pRet->pos;
            InterpolateRotation(&mMovement.rotation.y, targetRotation, pRet->rotationSpeed);

            if ((int)pConfig->minStateDuration < mMovement.stateTimer) {
                if (RPUtlRandom::getU32(pConfig->idleToPatrolChanceDenom) == 0) {
                    mMovement.behaviorState = 1;
                    mMovement.stateTimer = 0;

                    f32 walkSpeed = pConfig->minWalkSpeed + RPUtlRandom::getF32() * (pConfig->maxWalkSpeed - pConfig->minWalkSpeed);
                    if (RPUtlRandom::getU32(2) == 0) {
                        walkSpeed *= -1.0f;
                    }
                    mMovement.velocity.x = walkSpeed;
                }
            }
            break;
        }
    }

    mMovement.stateTimer++;

    if (pOutPosition != nullptr) {
        *pOutPosition = localVec;
    }
    if (pOutStateFlag != nullptr) {
        *pOutStateFlag = stateFlag;
    }
}

//! Gets the face model
#define GET_FACE(pKokeshi) ((pKokeshi)->mModelA4)
//! Gets the body model
#define GET_BODY(pKokeshi) ((pKokeshi)->mModelA8)
//! Gets the left hand model
#define GET_LHAND(pKokeshi) ((pKokeshi)->mModelAC)
//! Gets the right hand model
#define GET_RHAND(pKokeshi) ((pKokeshi)->mModelB0)

/**
 * @brief Renders the background NPC
 */
void RPBowBackgroundNpcManager::Render() {
    BackgroundNpcConfig* pConfig = &gBackgroundNpcParams;
    bool stateFlag = true;
    nw4r::math::VEC3 position(0.0f, 0.0f, 0.0f);

    UpdateMovement(&position, &stateFlag);

    if (!stateFlag || !unk_0x94) {
        return;
    }

    nw4r::math::MTX34 mtx;
    nw4r::math::MTX34Identity(&mtx);

    position += mMovement.position;
    if (lbl_806F5958 != 0) {
        position.y += pConfig->seatedPosY - pConfig->basePosY;
    }

    nw4r::math::MTX34Trans(&mtx, &position, &mtx);

    nw4r::math::MTX34 mtx2;
    nw4r::math::MTX34RotXYZDeg(&mtx2, mMovement.rotation.x, mMovement.rotation.y, mMovement.rotation.z);

    nw4r::math::MTX34Mult(&mtx, &mtx, &mtx2);

    nw4r::math::VEC3 scale(0.7f, 0.7f, 0.7f);
    nw4r::math::MTX34 mtx3 = mtx;

    mtx3._10 *= -1.0f;
    mtx3._11 *= -1.0f;
    mtx3._12 *= -1.0f;
    mtx3._13 *= -1.0f;
    mtx3._13 += pConfig->mirroredModelZOffset;

    for (int i = 0; i < 2; i++) {
        RPGrpModel* pBody;
        NpcModelGroup* pGroup = mModelGroups[mModelGroupSet][i];

        nw4r::math::MTX34 leftHandMtx;
        nw4r::math::MTX34 rightHandMtx;
        nw4r::math::MTX34 headMtx;

        GET_BODY(pGroup)->Unk_801E5D00(i == 0 ? &mtx : &mtx3);
        fn_8024DD14(GET_BODY(pGroup), &scale);
        GET_BODY(pGroup)->UpdateFrame();
        pBody = GET_BODY(pGroup);
        pBody->SetCallback(reinterpret_cast<IRPGrpModelCallback*>(fn_804D2B10(&mIdleState)));
        GET_BODY(pGroup)->Calc();

        fn_802478BC(pGroup, &headMtx);
        fn_8024789C(pGroup, &leftHandMtx);
        fn_8024787C(pGroup, &rightHandMtx);

        if (i != 0) {
            nw4r::math::MTX34 flipMtx(
               -1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f
            );
            nw4r::math::MTX34Mult(&headMtx, &headMtx, &flipMtx);
        }

        GET_FACE(pGroup)->Unk_801E5D00(&headMtx);
        fn_8024DD14(GET_FACE(pGroup), &scale);
        GET_FACE(pGroup)->UpdateFrame();
        GET_FACE(pGroup)->Calc();

        GET_LHAND(pGroup)->Unk_801E5D00(&leftHandMtx);
        fn_8024DD14(GET_LHAND(pGroup), &scale);
        GET_LHAND(pGroup)->UpdateFrame();
        GET_LHAND(pGroup)->Calc();

        GET_RHAND(pGroup)->Unk_801E5D00(&rightHandMtx);
        fn_8024DD14(GET_RHAND(pGroup), &scale);
        GET_RHAND(pGroup)->UpdateFrame();
        GET_RHAND(pGroup)->Calc();

        if (i == 1 && !lbl_806F5958) {
            break;
        }

        GET_BODY(pGroup)->Entry();
        GET_FACE(pGroup)->Entry();
        GET_LHAND(pGroup)->Entry();
        GET_RHAND(pGroup)->Entry();
    }
}

/**
 * @brief Unknown stub
 */
void RPBowBackgroundNpcManager::fn_8034DD08() {
    ;
}

} // namespace Bowling

// Tables of this unit written out as data under their address labels (vtables:
// slot 0 = RTTI, slot 1 = this-offset; the classes are not modelled with their
// full virtual lists yet).
extern "C" {
void fn_8034E83C__Q27Bowling25RPBowBackgroundNpcManagerFv();
void Render__Q27Bowling25RPBowBackgroundNpcManagerFv();
void fn_8034DD08__Q27Bowling25RPBowBackgroundNpcManagerFv();
void fn_804C7B60();
void fn_804C7D14();
void fn_804C7D10();
void ListenPropertyEvent__18IRPSysHostIOSocketFv();
void GenMessage__18IRPSysHostIOSocketFv();

void* lbl_806DEA08[] = {
    0,
    0,
    (void*)Bowling::__dt__Q27Bowling25RPBowBackgroundNpcManagerFv,
    (void*)fn_8034E83C__Q27Bowling25RPBowBackgroundNpcManagerFv,
    (void*)Render__Q27Bowling25RPBowBackgroundNpcManagerFv,
    (void*)fn_8034DD08__Q27Bowling25RPBowBackgroundNpcManagerFv,
    (void*)fn_804C7B60,
    (void*)fn_804C7D14,
    (void*)fn_804C7D10,
    0,
    0,
    (void*)ListenPropertyEvent__18IRPSysHostIOSocketFv,
    (void*)GenMessage__18IRPSysHostIOSocketFv,
    0,
};
}  // extern "C"
