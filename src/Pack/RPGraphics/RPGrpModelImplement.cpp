#include <Pack/RPGraphics.h>

#include <nw4r/g3d.h>

// Resort emits the strong functions of this file in reverse source order:
// the definitions below run from the highest address (Construct, 0x802522C4)
// down to GetCallbackJointIndex (0x80250F64). The file itself starts lower,
// at 0x80250BFC (VF_0x80 ... SetShapeVisible are declared in the header and
// still sit in unk/text_80250868).

namespace {

/**
 * Resort's nw4r resource accessors are single expressions; with
 * optimize_for_size the inliner only expands IsValid/ptr/ref nested inside
 * such expression bodies (the if-statement forms in our nw4r headers leave
 * them as weak calls, as IsJointVisible still shows). Local copies until the
 * nw4r headers carry the Resort forms.
 */
inline u32 GetResNodeID(const nw4r::g3d::ResNode node) {
    return node.IsValid() ? node.ptr()->id : 0;
}

inline u32 GetResNodeMtxID(const nw4r::g3d::ResNode node) {
    return node.IsValid() ? node.ptr()->mtxID : 0;
}

inline const char* GetResNodeName(const nw4r::g3d::ResNode node) {
    return node.ofs_to_ptr<char>(node.ref().name);
}

inline const char* GetResMatName(const nw4r::g3d::ResMat mat) {
    return mat.ofs_to_ptr<char>(mat.ref().name);
}

} // namespace

template <>
RPGrpModelAnm*
RPGrpModelAnmImplement<RPGrpModel::Kind_G3D>::Construct(RPGrpModel* pModel) {
    RPGrpModelAnm* pAnm = new RPGrpModelAnmImplement(pModel);
    pAnm->Configure();
    return pAnm;
}

RPGrpModelG3D::RPGrpModelG3D(RPGrpHandle handle, u8 viewNo, u32 typeOption,
                             u32 bufferOption)
    : RPGrpModel(viewNo), mUnk54(NULL) {

    Unk_80251FBC(RPGrpModelResManager::GetCurrent()
                     ->GetData<RPGrpModelResManager::Type_ResMdl>(handle),
                 viewNo, typeOption, bufferOption);
}

RPGrpModelG3D::RPGrpModelG3D(RPGrpHandle handle, const char* pName, u8 viewNo,
                             u32 typeOption, u32 bufferOption)
    : RPGrpModel(viewNo), mUnk54(NULL) {

    Unk_80251FBC(RPGrpModelResManager::GetCurrent()
                     ->GetData<RPGrpModelResManager::Type_ResMdl>(handle, pName),
                 viewNo, typeOption, bufferOption);
}

RPGrpModelG3D::RPGrpModelG3D(RPGrpHandle handle, int idx, u8 viewNo,
                             u32 typeOption, u32 bufferOption)
    : RPGrpModel(viewNo), mUnk54(NULL) {

    Unk_80251FBC(RPGrpModelResManager::GetCurrent()
                     ->GetData<RPGrpModelResManager::Type_ResMdl>(handle, idx),
                 viewNo, typeOption, bufferOption);
}

RPGrpModelG3D::RPGrpModelG3D(nw4r::g3d::ResMdl mdl, u8 viewNo, u32 typeOption,
                             u32 bufferOption)
    : RPGrpModel(viewNo) {

    Unk_80251FBC(mdl, viewNo, typeOption, bufferOption);
}

void RPGrpModelG3D::Unk_80251FBC(nw4r::g3d::ResMdl mdl, u8 viewNo,
                                 u32 typeOption, u32 bufferOption) {
    nw4r::g3d::ScnObj* pScnObj;
    u32 size;

    if (bufferOption == 0 && !(typeOption & TypeOption_NoSimple)) {
        pScnObj = nw4r::g3d::ScnMdlSimple::Construct(GetAllocator(), &size,
                                                     mdl, viewNo);
    } else {
        pScnObj = nw4r::g3d::ScnMdl::Construct(GetAllocator(), &size, mdl,
                                               bufferOption, viewNo);
    }

    mpModelEx = new EGG::ModelEx(pScnObj);

    // TODO(Resort): if (typeOption & 2) the ModelEx method 0x801B43D0 is
    // called with 1; it is not declared in eggModelEx.h yet.
}

void RPGrpModelG3D::Unk_80251F7C(const RPGrpModel* pModel) {
    mUnk54 = pModel->VF_0x90();
}

void RPGrpModelG3D::Configure() {
    RPGrpModel::Configure();

    if (GetScnMdlSimple() != NULL) {
        GetScnMdlSimple()->SetScnObjCallback(this);
        GetScnMdlSimple()->SetScnMdlCallback(this);

        GetScnMdlSimple()->EnableScnObjCallbackTiming(
            static_cast<nw4r::g3d::ScnObj::Timing>(
                nw4r::g3d::ScnObj::CALLBACK_TIMING_A |
                nw4r::g3d::ScnObj::CALLBACK_TIMING_C));

        GetScnMdlSimple()->EnableScnObjCallbackExecOp(
            nw4r::g3d::ScnObj::EXECOP_CALC_MAT);
    }

    InternalCalc();
}

void RPGrpModelG3D::CreateAnm() {
    if (GetScnMdlSimple() != NULL) {
        mpModelAnm = RPGrpModelAnmG3D::Construct(this);
    }
}

IRPGrpModelCallback*
RPGrpModelG3D::SetCallback(IRPGrpModelCallback* pCallback) {
    if (GetScnMdlSimple() != NULL) {
        IRPGrpModelCallback* pOldCallback = mpCallback;
        mpCallback = pCallback;

        if (pCallback != NULL) {
            GetScnMdlSimple()->EnableScnMdlCallbackTiming(
                nw4r::g3d::ScnObj::CALLBACK_TIMING_ALL);
        } else {
            GetScnMdlSimple()->DisableScnMdlCallbackTiming(
                nw4r::g3d::ScnObj::CALLBACK_TIMING_ALL);
        }

        return pOldCallback;
    }

    return NULL;
}

void RPGrpModelG3D::VF_0xA4(const nw4r::math::VEC3& rScale) {
    if (!mReverseCulling) {
        GetScnLeaf()->SetScale(rScale);
    } else {
        const nw4r::math::_VEC3& rMag = GEOMETRY_MAGNIFY[mReverseCulling];

        nw4r::math::VEC3 scale(rScale.x * rMag.x, rScale.y * rMag.y,
                               rScale.z * rMag.z);

        GetScnLeaf()->SetScale(scale);
    }
}

void RPGrpModelG3D::VF_0xA8(u8 /* arg */) {
    u8 opa = spUnk_806F4DD4[mDrawGroup] + unk3;
    u8 xlu = spUnk_806F4DD8[mDrawGroup] + unk4;

    nw4r::g3d::ScnObj* pScnObj =
        !(mFlags & 0x8) ? GetScnObj() : VF_0x90();

    pScnObj->SetPriorityDrawOpa(opa);
    pScnObj->SetPriorityDrawXlu(xlu);
}

void RPGrpModelG3D::InternalCalc() {
    const nw4r::math::MTX34* pLocalMtx =
        GetScnObj()->GetMtxPtr(nw4r::g3d::ScnObj::MTX_LOCAL);
    nw4r::g3d::ScnLeaf* pScnLeaf = GetScnLeaf();

    if (mpRecord != NULL && GetScnMdlSimple() != NULL) {
        GetScnMdlSimple()->EnableScnMdlCallbackTiming(
            nw4r::g3d::ScnMdl::CALLBACK_TIMING_C);
    }

    if (mFlags & 0x8) {
        mUnk54->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, pLocalMtx);
    }

    if (!(mFlags & 0x80)) {
        GetScnObj()->G3dProc(nw4r::g3d::G3dObj::G3DPROC_CALC_WORLD, 0, NULL);
    } else {
        const nw4r::math::_VEC3& rScale = pScnLeaf->GetScale();
        nw4r::math::VEC3 scale(rScale);
        nw4r::math::MTX34 worldMtx;

        pScnLeaf->SetMtx(nw4r::g3d::ScnObj::MTX_WORLD,
                         nw4r::math::MTX34Scale(&worldMtx, pLocalMtx, &scale));
    }
}

void RPGrpModelG3D::CalcBeforeDraw() {
    RPGrpModel::CalcBeforeDraw();

    if (mpCallback != NULL && GetScnMdlSimple() != NULL) {
        spCalcViewMtxArray = GetScnMdlSimple()->GetViewPosMtxArray();
        spCalcModel = this;

        mpCallback->ReferViewMtx(this);

        spCalcViewMtxArray = NULL;
        spCalcModel = NULL;
    }

    VF_0x84();
}

nw4r::g3d::ScnGroup* RPGrpModelG3D::VF_0x90() const {
    return mUnk54;
}

void RPGrpModelG3D::VF_0xB0() {
    mFlagBitEntered = false;
    mFlagBit100 = false;

    if (VF_0x90() != NULL) {
        VF_0x90()->Clear();
    }
}

void RPGrpModelG3D::SetJointVisible(u32 idx, bool enable) {
    if (GetScnMdl() != NULL) {
        nw4r::g3d::ScnMdl::CopiedVisAccess access(GetScnMdl(), idx);
        access.SetVisibilityEx(enable);
    } else {
        GetScnMdlSimple()->GetResMdl().GetResNode((int)idx).SetVisibility(enable);
    }
}

bool RPGrpModelG3D::IsJointVisible(u32 idx) const {
    if (GetScnMdl() != NULL) {
        nw4r::g3d::ScnMdl::CopiedVisAccess access(GetScnMdl(), idx);
        return access.IsVisible();
    } else {
        return GetScnMdlSimple()->GetResMdl().GetResNode((int)idx).IsVisible();
    }
}

void RPGrpModelG3D::ExecCallback_CALC_MAT(
    nw4r::g3d::ScnObj::Timing /* timing */, nw4r::g3d::ScnObj* /* pObj */,
    u32 /* param */, void* /* pInfo */) {}

void RPGrpModelG3D::ExecCallbackA(nw4r::g3d::ChrAnmResult* pResult,
                                  nw4r::g3d::ResMdl /* mdl */,
                                  nw4r::g3d::FuncObjCalcWorld* pFuncObj) {
    nw4r::math::MTX34 trans;
    nw4r::math::VEC3 scale;

    pResult->GetRotTrans(&trans);
    pResult->GetScale(&scale);

    mpCallback->EditJointLocalMtx(
        this, GetScnMdlSimple()->GetScnMdlCallbackNodeID(), &trans, &scale);

    pResult->SetRotTrans(&trans);
    pResult->SetScale(&scale);

    pFuncObj->SetCallbackNodeID(GetScnMdlSimple()->GetScnMdlCallbackNodeID());
}

void RPGrpModelG3D::ExecCallbackB(nw4r::g3d::WorldMtxManip* pManip,
                                  nw4r::g3d::ResMdl /* mdl */,
                                  nw4r::g3d::FuncObjCalcWorld* pFuncObj) {
    static nw4r::math::MTX34 jointWorldMtx;

    pManip->GetMtx(&jointWorldMtx);

    mpCallback->EditJointWorldMtx(
        this, GetScnMdlSimple()->GetScnMdlCallbackNodeID(), &jointWorldMtx);

    pManip->SetMtx(&jointWorldMtx);

    pFuncObj->SetCallbackNodeID(GetScnMdlSimple()->GetScnMdlCallbackNodeID());
}

void RPGrpModelG3D::ExecCallbackC(nw4r::math::MTX34* pMtxArray,
                                  nw4r::g3d::ResMdl /* mdl */,
                                  nw4r::g3d::FuncObjCalcWorld* /* pFuncObj */) {
    spCalcWorldMtxArray = pMtxArray;
    spCalcModel = this;

    if (mpCallback != NULL) {
        mpCallback->EditWorldMtx(this);
    }

    if (mpRecord != NULL) {
        mpRecord->Calc(this);
    }

    spCalcWorldMtxArray = NULL;
    spCalcModel = NULL;
}

nw4r::math::MTX34* RPGrpModelG3D::ReferWorldMtx(u16 nodeIdx) const {
    u32 idx = GetResNodeMtxID(GetScnMdlSimple()->GetResMdl().GetResNode(nodeIdx));
    return &spCalcWorldMtxArray[idx];
}

void RPGrpModelG3D::GetWorldMtx(u16 idx, nw4r::math::MTX34* pMtx) const {
    GetScnMdlSimple()->GetScnMtxPos(pMtx, nw4r::g3d::ScnObj::MTX_WORLD, idx);
}

const nw4r::math::MTX34* RPGrpModelG3D::GetWorldMtxPtr(u16 nodeIdx) const {
    u32 idx = GetResNodeMtxID(GetScnMdlSimple()->GetResMdl().GetResNode(nodeIdx));
    return &GetScnMdlSimple()->GetWldMtxArray()[idx];
}

void RPGrpModelG3D::GetViewMtx(u16 nodeIdx, nw4r::math::MTX34* pMtx) const {
    u32 idx = GetResNodeMtxID(GetScnMdlSimple()->GetResMdl().GetResNode(nodeIdx));
    nw4r::math::MTX34Copy(pMtx, &spCalcViewMtxArray[idx]);
}

const char* RPGrpModelG3D::GetJointName(u16 idx) const {
    return GetResNodeName(GetScnMdlSimple()->GetResMdl().GetResNode(idx));
}

u16 RPGrpModelG3D::GetJointIndex(const char* pName) const {
    return GetResNodeID(GetScnMdlSimple()->GetResMdl().GetResNode(pName));
}

const char* RPGrpModelG3D::GetMaterialName(u16 idx) const {
    return GetResMatName(GetScnMdlSimple()->GetResMdl().GetResMat(idx));
}

u16 RPGrpModelG3D::GetMaterialIndex(const char* pName) const {
    return GetScnMdlSimple()->GetResMdl().GetResMat(pName).GetID();
}

void RPGrpModelG3D::SetCallbackJointIndex(u16 idx) {
    GetScnMdlSimple()->SetScnMdlCallbackNodeID(idx);
}

u16 RPGrpModelG3D::GetCallbackJointIndex() const {
    return GetScnMdlSimple()->GetScnMdlCallbackNodeID();
}
