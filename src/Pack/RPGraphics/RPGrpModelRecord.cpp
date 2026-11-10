// The shared headers pull in g3d_gpu.h (`static const u8 cm2hw[]`), which emits a
// stray .sdata2 entry this object lacks. Pre-define its include guard.
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPGraphics/RPGrpModel.h>
#include <Pack/RPGraphics/RPGrpModelRecord.h>

RPGrpModelRecord::~RPGrpModelRecord() {}

RPGrpModelRecordJointBuffer::~RPGrpModelRecordJointBuffer() {}

#pragma dont_inline on
RPGrpModelRecordBuffer::RPGrpModelRecordBuffer(u16 frames) {
    int n = frames;
    mNumFrames = n;
    mpSamples = NULL;
    mpSamples = new RPGrpModelRecordSample[n];
}
#pragma dont_inline reset

RPGrpModelRecord::RPGrpModelRecord(u16 frames, RPGrpModel* pModel) {
    u16 numJoints = pModel->GetJointNum() == 0 ? 1 : pModel->GetJointNum();
    mpBuffer = new RPGrpModelRecordJointBuffer(frames, numJoints);
    mSample.pJoints = new RPGrpModelRecordMtx[numJoints];
}

void RPGrpModelRecord::Clear() {
    for (int i = 0; i < mpBuffer->mNumJoints; i++) {
        nw4r::math::MTX34Identity(&mSample.pJoints[i]);
    }
    nw4r::math::MTX34Identity(&mSample.baseMtx);

    mpBuffer->ResetAll();

    mFlags = 0;
    mFrame = 0.0f;
    mIndex = 0;
}

void RPGrpModelRecord::Calc(RPGrpModel* pModel) {
    u16 numJoints = pModel->GetJointNum() == 0 ? 1 : pModel->GetJointNum();

    if (mFlags & EFlag_Record) {
        for (int i = 0; i < numJoints; i++) {
            nw4r::math::MTX34Copy(&mSample.pJoints[i],
                                  pModel->ReferWorldMtx(i));
        }
        nw4r::math::MTX34Copy(
            &mSample.baseMtx,
            pModel->GetScnObj()->GetMtxPtr(nw4r::g3d::ScnObj::MTX_LOCAL));
        mpBuffer->Store(&mpBuffer->mpSamples[mIndex], &mSample);
    } else if (mFlags & EFlag_Play) {
        f32 frame = mFrame;
        int idx = static_cast<int>(frame);
        u16 next = idx + 1;
        if (next >= mpBuffer->mNumFrames) {
            next = 0;
        }
        f32 t = frame - static_cast<int>(frame);
        mpBuffer->Lerp(&mSample, &mpBuffer->mpSamples[static_cast<u16>(idx)],
                       &mpBuffer->mpSamples[next], t);

        for (int i = 0; i < numJoints; i++) {
            nw4r::math::MTX34Copy(pModel->ReferWorldMtx(i),
                                  &mSample.pJoints[i]);
        }

        nw4r::g3d::ScnObj* pScnObj = pModel->GetScnObj();
        if (pScnObj != NULL) {
            pScnObj->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &mSample.baseMtx);
        }
    }

    mFlags = 0;
}

RPGrpModelRecordMtx::RPGrpModelRecordMtx() {}

RPGrpModelRecordBuffer::~RPGrpModelRecordBuffer() {}

void RPGrpModelRecordJointBuffer::Store(RPGrpModelRecordSample* pDst,
                                        const RPGrpModelRecordSample* pSrc) {
    for (int i = 0; i < mNumJoints; i++) {
        nw4r::math::MTX34Copy(&pDst->pJoints[i], &pSrc->pJoints[i]);
    }
    nw4r::math::MTX34Copy(&pDst->baseMtx, &pSrc->baseMtx);
}

void RPGrpModelRecordJointBuffer::Lerp(RPGrpModelRecordSample* pDst,
                                       const RPGrpModelRecordSample* pA,
                                       const RPGrpModelRecordSample* pB,
                                       f32 t) {
    f32 u = 1.0f - t;

    for (int i = 0; i < mNumJoints; i++) {
        EGG::Matrix34f* pMtxD = &pDst->pJoints[i];
        const EGG::Matrix34f* pMtxA = &pA->pJoints[i];
        const EGG::Matrix34f* pMtxB = &pB->pJoints[i];

        nw4r::math::VEC3 colA0(pMtxA->_00, pMtxA->_10, pMtxA->_20);
        nw4r::math::VEC3 colA1(pMtxA->_01, pMtxA->_11, pMtxA->_21);
        nw4r::math::VEC3 colA2(pMtxA->_02, pMtxA->_12, pMtxA->_22);
        nw4r::math::VEC3 colB0(pMtxB->_00, pMtxB->_10, pMtxB->_20);
        nw4r::math::VEC3 colB1(pMtxB->_01, pMtxB->_11, pMtxB->_21);
        nw4r::math::VEC3 colB2(pMtxB->_02, pMtxB->_12, pMtxB->_22);

        nw4r::math::VEC3 crossA;
        nw4r::math::VEC3Cross(&crossA, &colA1, &colA2);
        nw4r::math::VEC3 crossB;
        nw4r::math::VEC3Cross(&crossB, &colB1, &colB2);

        nw4r::math::VEC3 scaleA(
            (nw4r::math::VEC3Dot(&colA0, &crossA) > 0.0f ? 1.0f : -1.0f) *
                nw4r::math::FSqrt(pMtxA->_00 * pMtxA->_00 +
                                  pMtxA->_10 * pMtxA->_10 +
                                  pMtxA->_20 * pMtxA->_20),
            nw4r::math::FSqrt(pMtxA->_01 * pMtxA->_01 +
                              pMtxA->_11 * pMtxA->_11 +
                              pMtxA->_21 * pMtxA->_21),
            nw4r::math::FSqrt(pMtxA->_02 * pMtxA->_02 +
                              pMtxA->_12 * pMtxA->_12 +
                              pMtxA->_22 * pMtxA->_22));

        nw4r::math::VEC3 scaleB(
            (nw4r::math::VEC3Dot(&colB0, &crossB) > 0.0f ? 1.0f : -1.0f) *
                nw4r::math::FSqrt(pMtxB->_00 * pMtxB->_00 +
                                  pMtxB->_10 * pMtxB->_10 +
                                  pMtxB->_20 * pMtxB->_20),
            nw4r::math::FSqrt(pMtxB->_01 * pMtxB->_01 +
                              pMtxB->_11 * pMtxB->_11 +
                              pMtxB->_21 * pMtxB->_21),
            nw4r::math::FSqrt(pMtxB->_02 * pMtxB->_02 +
                              pMtxB->_12 * pMtxB->_12 +
                              pMtxB->_22 * pMtxB->_22));

        nw4r::math::VEC3 scale(u * scaleA.x + t * scaleB.x,
                               u * scaleA.y + t * scaleB.y,
                               u * scaleA.z + t * scaleB.z);
        nw4r::math::VEC3 invA(1.0f / scaleA.x, 1.0f / scaleA.y,
                              1.0f / scaleA.z);
        nw4r::math::VEC3 invB(1.0f / scaleB.x, 1.0f / scaleB.y,
                              1.0f / scaleB.z);

        EGG::Matrix34f mtxA = *pMtxA;
        mtxA._00 *= invA.x;
        mtxA._10 *= invA.x;
        mtxA._20 *= invA.x;
        mtxA._01 *= invA.y;
        mtxA._11 *= invA.y;
        mtxA._21 *= invA.y;
        mtxA._02 *= invA.z;
        mtxA._12 *= invA.z;
        mtxA._22 *= invA.z;

        EGG::Matrix34f mtxB = *pMtxB;
        mtxB._00 *= invB.x;
        mtxB._10 *= invB.x;
        mtxB._20 *= invB.x;
        mtxB._01 *= invB.y;
        mtxB._11 *= invB.y;
        mtxB._21 *= invB.y;
        mtxB._02 *= invB.z;
        mtxB._12 *= invB.z;
        mtxB._22 *= invB.z;

        nw4r::math::QUAT quat;
        nw4r::math::QUAT quatA;
        nw4r::math::QUAT quatB;
        nw4r::math::MTX34ToQUAT(&quatA, &mtxA);
        nw4r::math::MTX34ToQUAT(&quatB, &mtxB);
        nw4r::math::C_QUATSlerp(&quat, &quatA, &quatB, t);
        nw4r::math::QUATToMTX34(pMtxD, &quat);

        pMtxD->_00 *= scale.x;
        pMtxD->_10 *= scale.x;
        pMtxD->_20 *= scale.x;
        pMtxD->_01 *= scale.y;
        pMtxD->_11 *= scale.y;
        pMtxD->_21 *= scale.y;
        pMtxD->_02 *= scale.z;
        pMtxD->_12 *= scale.z;
        pMtxD->_22 *= scale.z;

        pMtxD->_03 = u * pMtxA->_03 + t * pMtxB->_03;
        pMtxD->_13 = u * pMtxA->_13 + t * pMtxB->_13;
        pMtxD->_23 = u * pMtxA->_23 + t * pMtxB->_23;
    }

    nw4r::math::QUAT quat;
    nw4r::math::QUAT quatA;
    nw4r::math::QUAT quatB;
    nw4r::math::MTX34ToQUAT(&quatA, &pA->baseMtx);
    nw4r::math::MTX34ToQUAT(&quatB, &pB->baseMtx);
    nw4r::math::C_QUATSlerp(&quat, &quatA, &quatB, t);
    nw4r::math::QUATToMTX34(&pDst->baseMtx, &quat);

    pDst->baseMtx._03 = u * pA->baseMtx._03 + t * pB->baseMtx._03;
    pDst->baseMtx._13 = u * pA->baseMtx._13 + t * pB->baseMtx._13;
    pDst->baseMtx._23 = u * pA->baseMtx._23 + t * pB->baseMtx._23;
}

void RPGrpModelRecordJointBuffer::Reset(RPGrpModelRecordSample* pSample) {
    for (int i = 0; i < mNumJoints; i++) {
        nw4r::math::MTX34Identity(&pSample->pJoints[i]);
    }
    nw4r::math::MTX34Identity(&pSample->baseMtx);
}
