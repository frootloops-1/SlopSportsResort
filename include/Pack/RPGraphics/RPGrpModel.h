#ifndef RP_GRAPHICS_MODEL_H
#define RP_GRAPHICS_MODEL_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpModelResManager.h>

#include <egg/core.h>
#include <egg/gfxe.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class IRPGrpModelCallback;
class RPGrpModelAnm;
class RPGrpModelBoundingInfo;
class RPGrpModelMaterial;
class RPGrpModelRecord;
class RPGrpTexture;

/**
 * @brief Base class for model implementations
 */
class RPGrpModel {
    //! The model manager owns the global model state
    friend class RPGrpModelManager;
    //! The model scene reads the entry list and priority state
    friend class RPGrpModelScene;

public:
    /**
     * @brief Model class type
     */
    enum Kind {
        Kind_None, //!< Dummy value
        Kind_G3D,  //!< RPGrpModelG3D
        Kind_RFL,  //!< RPGrpModelRfl
    };

    /**
     * @brief Model creation type flags
     */
    enum TypeOption {
        TypeOption_NoSimple = 1 << 0, //!< Require ScnMdl even without buffers
    };

    /**
     * @brief Bound creation type flags
     */
    enum BoundOption {
        BoundOption_Sphere = 1 << 0,
        BoundOption_SphereSet = 1 << 1,
        BoundOption_AABB = 1 << 2,
        BoundOption_AABBSet = 1 << 3,
    };

protected:
    u8 mViewNo;    // at 0x0
    u8 mDrawScene; // at 0x1
    u8 mDrawGroup; // at 0x2
    u8 unk3; // Resort: opa priority offset (0x80251B20)
    u8 unk4; // Resort: xlu priority offset (0x80251B20)
    char unk5[0x8 - 0x5];
    // Resort clears single flags through bitfields (rlwinm, not andi.:
    // 0x8024E8EC, 0x8025184C, 0x80250C9C). Bit names unknown except the
    // EFlag_* values below.
    union {
        u16 mFlags; // at 0x8
        struct {
            u16 mFlagBitsFC00 : 6;
            u16 mFlagBit200 : 1;
            u16 mFlagBit100 : 1;
            u16 mFlagBit80 : 1;
            u16 mFlagBit40 : 1;
            u16 mFlagBit20 : 1;
            u16 mFlagBit10 : 1;
            u16 mFlagBit8 : 1;
            u16 mFlagBitHasRecord : 1; // 0x4
            u16 mFlagBitEntered : 1;   // 0x2
            u16 mFlagBitVisible : 1;   // 0x1
        };
    };
    u16 unkA;
    // Resort layout (ctor 0x8024E46C stores 0x0-0x44, vtable at 0x48;
    // Entry 0x8024E054, CreateRecord 0x8024E2F0, CreateBoundingInfo
    // 0x8024E34C, CreateMaterial 0x8024E1FC, SetCallback 0x80251C40,
    // reverse-culling scale 0x80251BB4). ogws order differs.
    u32 unkC;
    BOOL mReverseCulling;                   // at 0x10
    u32 mUnk14;                             // at 0x14
    nw4r::math::VEC3 mBaseScale;            // at 0x18
    RPGrpModel* mpEntryNext;                // at 0x24
    RPGrpModel* mpGenNext;                  // at 0x28
    IRPGrpModelCallback* mpCallback;        // at 0x2C
    RPGrpModelRecord* mpRecord;             // at 0x30
    RPGrpModelBoundingInfo* mpBoundingInfo; // at 0x34
    RPGrpModelMaterial** mppMaterials;      // at 0x38
    void* mUnk3C;                           // at 0x3C
    RPGrpModelAnm* mpModelAnm;              // at 0x40
    EGG::ModelEx* mpModelEx;                // at 0x44

public:
    static RPGrpModel* Construct(RPGrpHandle handle, u8 viewNo, u32 typeOption,
                                 u32 bufferOption);

    static RPGrpModel* Construct(RPGrpHandle handle, int idx, u8 viewNo,
                                 u32 typeOption, u32 bufferOption);

    static RPGrpModel* Construct(RPGrpHandle handle, const char* pName,
                                 u8 viewNo, u32 typeOption, u32 bufferOption);

    virtual UNKTYPE VF_0x8(UNKTYPE) = 0;  // at 0x8
    virtual UNKTYPE VF_0xC(UNKTYPE) = 0;  // at 0xC
    virtual UNKTYPE VF_0x10(UNKTYPE) = 0; // at 0x10

    virtual Kind GetKind() = 0; // at 0x14

    // Resort vtable (base lbl_806B9A08, RPGrpModelG3D lbl_806B9C50): slots
    // 0x18-0x58 below are verified; 0x5C-0x84 still use the ogws order and
    // are NOT verified (Resort: 0x5C-0x70 pure, 0x74 returns 0, CalcBeforeDraw
    // 0x88, CalcView 0x8C, dtor 0x94, Configure 0x98, GetShapeMinMax 0xAC).

    // fn_801F3D80: stores the argument to mDrawScene (0x1). Name unknown.
    virtual void VF_0x18(u8 arg); // at 0x18
    // fn_801F5438: stores the argument to mDrawGroup (0x2), then calls the
    // virtual at 0xA8. Name unknown.
    virtual void VF_0x1C(u8 arg); // at 0x1C
    // fn_8024E844: sets/clears mFlags bit 0x20. Name unknown.
    virtual void VF_0x20(bool enable); // at 0x20
    // fn_8024E86C: sets/clears mFlags bit 0x200. Name unknown.
    virtual void VF_0x24(bool enable); // at 0x24

    // fn_8024DC20 (called through 0x28 by RPSysKokeshiManager 0x80246218)
    virtual u16 ReplaceTexture(const char* pName, const RPGrpTexture& rTexture,
                               bool keepFilterWrap); // at 0x28

    // RPGrpModelG3D override 0x80251C40; base fn_801E5CF0 swaps mpCallback
    virtual IRPGrpModelCallback*
    SetCallback(IRPGrpModelCallback* pCallback); // at 0x2C

    virtual void SetCallbackJointIndex(u16 idx) = 0; // at 0x30
    virtual u16 GetCallbackJointIndex() const = 0;   // at 0x34

    virtual void SetJointVisible(u32 /* idx */, bool enable) { // at 0x38
        if (enable) {
            mFlags |= EFlag_Visible;
        } else {
            mFlags &= ~EFlag_Visible;
        }
    }

    virtual bool IsJointVisible(u32 /* idx */) const { // at 0x3C
        return mFlags & EFlag_Visible;
    }

    virtual void SetShapeVisible(u32 /* idx */, bool enable) { // at 0x40
        if (enable) {
            mFlags |= EFlag_Visible;
        } else {
            mFlags &= ~EFlag_Visible;
        }
    }

    virtual bool IsShapeVisible(u32 /* idx */) const { // at 0x44
        return mFlags & EFlag_Visible;
    }

    // fn_8024E8BC: mpModelEx's ScnObj->GetMtx(type 2, pMtx). Name unknown.
    virtual void VF_0x48(nw4r::math::MTX34* pMtx) const; // at 0x48

    virtual void GetWorldMtx(u16 idx,
                             nw4r::math::MTX34* pMtx) const = 0; // at 0x4C
    virtual const nw4r::math::MTX34*
    GetWorldMtxPtr(u16 nodeIdx) const = 0;                              // at 0x50
    virtual nw4r::math::MTX34* ReferWorldMtx(u16 nodeIdx) const = 0; // at 0x54

    virtual void GetViewMtx(u16 idx,
                            nw4r::math::MTX34* pMtx) const = 0; // at 0x58

    // 0x5C-0x70 are pure in the base; GetMaterialIndex at 0x68 is proven by
    // the weak GetMaterial(const char*) copy at 0x8021B210, the other names
    // follow the ogws order.
    virtual const char* GetJointName(u16 idx) const = 0;       // at 0x5C
    virtual u16 GetJointIndex(const char* pName) const = 0;    // at 0x60
    virtual const char* GetMaterialName(u16 idx) const = 0;    // at 0x64
    virtual u16 GetMaterialIndex(const char* pName) const = 0; // at 0x68
    virtual const char* GetShapeName(u16 idx) const = 0;       // at 0x6C
    virtual u16 GetShapeIndex(const char* pName) const = 0;    // at 0x70

    // Names unknown (base implementations in RPGrpModel.cpp):
    virtual u32 VF_0x74() const;   // at 0x74 (fn_8024E8D0: returns 0)
    // at 0x78 (fn_8024E2E0: mFlags |= 0x8; RPGrpModelG3D 0x80251D38 passes
    // the argument to ScnGroupEx::Construct)
    virtual void VF_0x78(u32 arg);
    virtual void VF_0x7C(void* p); // at 0x7C (fn_8024E1B4: stores to 0x3C)
    virtual void VF_0x80(void* p); // at 0x80 (fn_8024E188: stores to 0x3C)
    virtual void VF_0x84();        // at 0x84 (fn_8024E004)

    // fn_8024DE54 (Resort body differs from ogws)
    virtual void CalcBeforeDraw(); // at 0x88

    virtual void CalcView(const nw4r::math::MTX34& rViewMtx,
                          nw4r::math::MTX34* pViewMtxArray) { // at 0x8C

        if (pViewMtxArray != NULL) {
            mpModelEx->calcView(rViewMtx, pViewMtxArray);
            return;
        }

        if (GetScnObj() != NULL) {
            GetScnObj()->G3dProc(nw4r::g3d::G3dObj::G3DPROC_CALC_VIEW, 0,
                                 const_cast<nw4r::math::MTX34*>(&rViewMtx));
        }
    }

    // at 0x90 (fn_8024E8D8: returns 0; RPGrpModelG3D 0x802518F8 returns
    // its scene group at 0x54, cleared by 0x8025184C via ScnGroup::Clear)
    virtual nw4r::g3d::ScnGroup* VF_0x90() const;

    // Not in the Resort vtable; kept non-virtual for the ogws-derived sources
    u16 GetJointNum() const {
        return mpModelEx->getNumNode();
    }
    u16 GetMaterialNum() const;
    u16 GetShapeNum() const {
        return mpModelEx->getNumShape();
    }
    u16 GetViewMtxNum() const {
        return mpModelEx->getNumViewMtx();
    }
    void DrawDirect(u32 drawFlag, nw4r::math::MTX34* pViewMtx) {
        mpModelEx->drawShapeDirectly(drawFlag, true, true, pViewMtx);
    }
    void CalcMaterial();

    RPGrpModelAnm* GetModelAnm() const {
        return mpModelAnm;
    }

    void SetDrawScene(u8 drawScene) {
        mDrawScene = drawScene;
    }

    void RemoveGenList();
    void CreateMaterial(u16 idx);
    void CreateBoundingInfo(u32 flags);
    void CreateRecord(u16 frames);
    void UpdateFrame(); // Resort: 0x8024E11C
    void Calc();        // Resort: 0x8024E08C
    void Entry();
    // Resort 0x801E5D00: mpModelEx's ScnObj->SetMtx(MTX_LOCAL, pMtx), no NULL
    // check (called by RPBowBallReturnRack::UpdateBallReturnRack). Name unknown.
    void Unk_801E5D00(const nw4r::math::MTX34* pMtx);

    EGG::ModelEx* GetModelEx() const {
        return mpModelEx;
    }

    nw4r::g3d::ScnObj* GetScnObj() const {
        return mpModelEx->getScnObj();
    }

    nw4r::g3d::ScnLeaf* GetScnLeaf() const {
        return mpModelEx->getScnLeaf();
    }

    nw4r::g3d::ScnMdlSimple* GetScnMdlSimple() const {
        return mpModelEx->getScnMdlSimple();
    }

    nw4r::g3d::ScnMdl* GetScnMdl() const {
        return mpModelEx->getScnMdl();
    }

    nw4r::g3d::ScnRfl* GetScnRfl() const {
        return mpModelEx->getScnRfl();
    }

    const nw4r::math::VEC3& GetBaseScale() const {
        return mBaseScale;
    }

    void SetBaseScale(const nw4r::math::VEC3& rBaseScale) {
        mBaseScale = rBaseScale;
    }

    void SetBaseScale(f32 x, f32 y, f32 z) {
        mBaseScale.x = x;
        mBaseScale.y = y;
        mBaseScale.z = z;
    }

    void SetBaseScale(f32 scale) {
        mBaseScale.x = mBaseScale.y = mBaseScale.z = scale;
    }

    // Resort: not inlined; the body (0x8021B210, mppMaterials[
    // GetMaterialIndex(pName)]) lives outside RPGrpModel.cpp
    RPGrpModelMaterial* GetMaterial(const char* pName) const;
    RPGrpModelMaterial* GetMaterial(u16 idx) const {
        return mppMaterials[idx];
    }

    bool IsVisible() const {
        return (mFlags & EFlag_Visible) ? true : false;
    }
    bool IsEntered() const {
        return (mFlags & EFlag_Entered) ? true : false;
    }

    /**
     * @brief Gets the allocator used for model-related allocations
     */
    static EGG::Allocator* GetAllocator() {
        return spAllocator;
    }
    /**
     * @brief Sets the allocator used for model-related allocations
     *
     * @param pAllocator New allocator
     */
    static void SetAllocator(EGG::Allocator* pAllocator) {
        spAllocator = pAllocator;
    }

protected:
    explicit RPGrpModel(u8 viewNo);
    virtual ~RPGrpModel(); // at 0x94

    virtual void Configure();        // at 0x98
    virtual void CreateAnm() = 0;    // at 0x9C
    virtual void InternalCalc() = 0; // at 0xA0

    // RPGrpModelG3D 0x80251BB4: sets the ScnObj scale from a VEC3 times
    // the GEOMETRY_MAGNIFY entry selected by 0x10. Name unknown.
    virtual void VF_0xA4(const nw4r::math::VEC3& rScale) = 0; // at 0xA4
    // Called by VF_0x1C with the new draw group. Name unknown.
    virtual void VF_0xA8(u8 arg) = 0; // at 0xA8

    virtual void GetShapeMinMax(u16 shapeIdx, nw4r::math::VEC3* pMin,
                                nw4r::math::VEC3* pMax) const { // at 0xAC
        mpModelEx->getShapeMinMax(shapeIdx, pMin, pMax, false);
    }

    // fn_8024E8EC: clears mFlags bits 0x2 and 0x100. Name unknown.
    virtual void VF_0xB0(); // at 0xB0

protected:
    enum {
        EFlag_Visible = 1 << 0,
        EFlag_Entered = 1 << 1,
        EFlag_HasRecord = 1 << 2,
    };

protected:
    static const nw4r::math::_VEC3 GEOMETRY_MAGNIFY[/* ??? */];

    //! Allocator used for model-related allocations
    static EGG::Allocator* spAllocator;

    //! First model in the draw ("entry") list
    static RPGrpModel* spEntryHead;
    //! Last model in the draw ("entry") list
    static RPGrpModel* spEntryTail;

    //! List of all active models in generation order
    static RPGrpModel* spGenList;

    //! Model currently running Calc
    static RPGrpModel* spCalcModel;

    static nw4r::math::MTX34* spCalcWorldMtxArray; // Resort: 0x806F4DCC
    static nw4r::math::MTX34* spCalcViewMtxArray;  // Resort: 0x806F4DD0

    // Resort: per-draw-group priority tables (0x806F4DD4 opa, 0x806F4DD8
    // xlu), read by RPGrpModelG3D 0x80251B20. Names unknown.
    static u8* spUnk_806F4DD4;
    static u8* spUnk_806F4DD8;
};

//! @}

#endif
