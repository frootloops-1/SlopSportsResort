#ifndef RP_GRAPHICS_MODEL_G3D_H
#define RP_GRAPHICS_MODEL_G3D_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpModel.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

//! @addtogroup rp_graphics
//! @{

/**
 * @brief Model implementation for nw4r::g3d
 *
 * Resort layout: RPGrpModel 0x0-0x4C (vtable at 0x48), IScnObjCallback at
 * 0x4C, ICalcWorldCallback at 0x50, scene group at 0x54 (ctors
 * 0x8025206C-0x8025221C, vtable lbl_806B9C50). Most virtuals are strong
 * out-of-line definitions in Resort (RPGrpModelImplement.cpp emits them in
 * reverse source order); only GetKind, VF_0x8/0x10/0xC and the dtor are
 * still emitted as weak copies after the strong functions.
 */
class RPGrpModelG3D : public RPGrpModel,
                      public nw4r::g3d::IScnObjCallback,
                      public nw4r::g3d::ICalcWorldCallback {
public:
    // Resort: 0x8025206C (does not clear the scene group)
    RPGrpModelG3D(nw4r::g3d::ResMdl mdl, u8 viewNo, u32 typeOption,
                  u32 bufferOption);

    // Resort: 0x802520EC
    RPGrpModelG3D(RPGrpHandle handle, int idx, u8 viewNo, u32 typeOption,
                  u32 bufferOption);

    // Resort: 0x80252184
    RPGrpModelG3D(RPGrpHandle handle, const char* pName, u8 viewNo,
                  u32 typeOption, u32 bufferOption);

    // Resort: 0x8025221C
    RPGrpModelG3D(RPGrpHandle handle, u8 viewNo, u32 typeOption,
                  u32 bufferOption);

    virtual ~RPGrpModelG3D() override {} // at 0x94

    virtual Kind GetKind() override { // at 0x14
        return Kind_G3D;
    }

    virtual IRPGrpModelCallback*
    SetCallback(IRPGrpModelCallback* pCallback) override; // at 0x2C

    virtual void SetCallbackJointIndex(u16 idx) override; // at 0x30
    virtual u16 GetCallbackJointIndex() const override;   // at 0x34

    virtual UNKTYPE VF_0x8(UNKTYPE) override {}  // at 0x8
    virtual UNKTYPE VF_0x10(UNKTYPE) override {} // at 0x10
    virtual UNKTYPE VF_0xC(UNKTYPE) override {}  // at 0xC

    // Resort: 0x80250C9C
    virtual void VF_0x20(bool enable) override; // at 0x20

    virtual void SetJointVisible(u32 idx, bool enable) override; // at 0x38
    virtual bool IsJointVisible(u32 idx) const override;         // at 0x3C

    virtual void SetShapeVisible(u32 idx, bool enable) override; // at 0x40
    virtual bool IsShapeVisible(u32 idx) const override;         // at 0x44

    virtual void GetWorldMtx(u16 idx,
                             nw4r::math::MTX34* pMtx) const override; // at 0x4C
    virtual const nw4r::math::MTX34*
    GetWorldMtxPtr(u16 nodeIdx) const override; // at 0x50
    virtual nw4r::math::MTX34*
    ReferWorldMtx(u16 nodeIdx) const override; // at 0x54
    virtual void GetViewMtx(u16 nodeIdx,
                            nw4r::math::MTX34* pMtx) const override; // at 0x58

    virtual const char* GetJointName(u16 idx) const override;       // at 0x5C
    virtual u16 GetJointIndex(const char* pName) const override;    // at 0x60
    virtual const char* GetMaterialName(u16 idx) const override;    // at 0x64
    virtual u16 GetMaterialIndex(const char* pName) const override; // at 0x68
    virtual const char* GetShapeName(u16 idx) const override;       // at 0x6C
    virtual u16 GetShapeIndex(const char* pName) const override;    // at 0x70

    // Resort: 0x80250CE4, 0x80251D38, 0x80250C4C, 0x80250BFC
    virtual u32 VF_0x74() const override;   // at 0x74
    virtual void VF_0x78(u32 arg) override; // at 0x78
    virtual void VF_0x7C(void* p) override; // at 0x7C
    virtual void VF_0x80(void* p) override; // at 0x80

    virtual void CalcBeforeDraw() override; // at 0x88

    // Resort: 0x802518F8
    virtual nw4r::g3d::ScnGroup* VF_0x90() const override; // at 0x90

    virtual void Configure() override;    // at 0x98
    virtual void CreateAnm() override;    // at 0x9C
    virtual void InternalCalc() override; // at 0xA0

    virtual void VF_0xA4(const nw4r::math::VEC3& rScale) override; // at 0xA4
    virtual void VF_0xA8(u8 arg) override;                         // at 0xA8

    // Resort: 0x8025184C
    virtual void VF_0xB0() override; // at 0xB0

    // Resort: 0x80251634 (the only IScnObjCallback override, empty)
    virtual void ExecCallback_CALC_MAT(nw4r::g3d::ScnObj::Timing timing,
                                       nw4r::g3d::ScnObj* pObj, u32 param,
                                       void* pInfo) override; // at 0x10

    virtual void
    ExecCallbackA(nw4r::g3d::ChrAnmResult* pResult, nw4r::g3d::ResMdl mdl,
                  nw4r::g3d::FuncObjCalcWorld* pFuncObj) override; // at 0xC

    virtual void
    ExecCallbackB(nw4r::g3d::WorldMtxManip* pManip, nw4r::g3d::ResMdl mdl,
                  nw4r::g3d::FuncObjCalcWorld* pFuncObj) override; // at 0x10

    virtual void
    ExecCallbackC(nw4r::math::MTX34* pMtxArray, nw4r::g3d::ResMdl mdl,
                  nw4r::g3d::FuncObjCalcWorld* pFuncObj) override; // at 0x14

    // Resort: 0x80251F7C, takes over the scene group of another model. Name
    // unknown.
    void Unk_80251F7C(const RPGrpModel* pModel);

private:
    // Resort: 0x80251FBC, shared ctor body: creates the scene model and the
    // EGG::ModelEx. Name unknown.
    void Unk_80251FBC(nw4r::g3d::ResMdl mdl, u8 viewNo, u32 typeOption,
                      u32 bufferOption);

    // Resort: scene group (ScnGroupEx, VF_0x78 0x80251D38). Name unknown.
    nw4r::g3d::ScnGroup* mUnk54; // at 0x54
};

//! @}

#endif
