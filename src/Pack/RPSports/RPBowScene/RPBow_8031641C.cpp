// Resort (RZTE01_01) port of Wii Sports RPBow_8031641C.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

// RPBow_8031641C: bowling scene object manager (Bowling::SomeUnkManager0 /
// SceneObjectManager). The manager holds 120 object pointers at 0x04, a lane
// table at 0x8C (8-byte entries) and a few mode flag bytes at 0x1F0..0x1F4.
// Types are inferred from use (invented); fn_ names are kept.
//
// Matching notes:
// - ogws_fn_80316C7C (scene resource setup) and ogws_fn_80318EB0 (object/Mii creation)
//   match instruction-for-instruction; only callee-saved register choice
//   differs, plus three lis/subi address pairs that have no relocation in the
//   split object (ActiveBall vtable at 0x803CA660, RPSysKokeshiOverloadInfo
//   vtable in the lane loop).
// - The string pool starts with three SJIS Mii-database labels owned by a
//   dead-stripped function (BowScene_StrippedDbNames placeholder).
// - Loop counters are declared per loop and the shadow-texture parameter copy
//   is one function-scope local: both are needed for the original spill-slot
//   and stack layout.
// - This unit's own .data (0x803CA3B0-0x803CA3E8) holds two vtables whose slot
//   functions live here; they are defined as hand arrays at the file end. The
//   other vtables used by the inlined constructors belong to the TUs of their
//   classes (RPBowMotionBlur.cpp, ...).

#pragma defer_codegen off


struct BowObj {
    virtual void v00();   // 0x08
    virtual void v0C();   // 0x0C
    virtual void v10(void*);  // 0x10
    virtual void v14();   // 0x14
    virtual void v18();   // 0x18
    virtual void v1C(int);  // 0x1C
    virtual void v20(int);  // 0x20
};

// Lane gfx object: non-polymorphic 0x44-byte base followed by the vptr.
struct BowShowBase {
    u8 pad000[0x44];
};

struct BowShowObj : BowShowBase {
    virtual void v00();      // 0x08
    virtual void v04();      // 0x0C
    virtual void v08();      // 0x10
    virtual void v0C();      // 0x14
    virtual void v10();      // 0x18
    virtual void show(s32);  // 0x1C
};

struct BowLaneGfx {
    u8 pad000[0xA4];
    BowShowObj* x_a4;  // 0xA4
    BowShowObj* x_a8;  // 0xA8
};

struct BowLaneEntry {
    BowLaneGfx* a;  // 0x8C
    BowLaneGfx* b;  // 0x90
};

static inline void BowShow(BowShowObj* o, s32 on) {
    o->show(on);
}

struct BowLaneMgr {
    u8 pad000[0x8C];
    BowLaneEntry ent[12];  // 0x8C
    u8 pad_ec[4];
    u8 flag[12];           // 0xF0
};

namespace nw4r {
namespace math {
struct VEC3 {
    f32 x, y, z;
    VEC3() {}
    VEC3(f32 a, f32 b, f32 c) : x(a), y(b), z(c) {}
};
}  // namespace math
}  // namespace nw4r
typedef nw4r::math::VEC3 BowVec3;

// Scene shadow texture (RPGrpShadowTexture : EGG::ShadowTexture): 0x14 bytes
// of non-polymorphic data, then the vptr.
struct BowShadowTexBase {
    u8 pad000[0x14];
};

struct BowShadowTex {
    virtual void v08();     // 0x08
    virtual void v0C();     // 0x0C
    virtual void update();  // 0x10
    virtual void v14();     // 0x14
    virtual void init();    // 0x18
    virtual void v1C();     // 0x1C
    u8 pad004[0x74 - 0x4];
    BowVec3 dir;            // 0x74
};

// Scene object with a world matrix at 0x44.
struct BowMtxObj {
    u8 pad000[0x44];
    f32 mtx[3][4];  // 0x44
    BowVec3 GetPos() const {
        return BowVec3(mtx[0][3], mtx[1][3], mtx[2][3]);
    }
};

struct BowSceneObjs {
    u8 pad000[0x04];
    BowObj* objs[121];  // 0x04
    u8 en[8];           // 0x1E8
    void* pad1EC;
    u8 b1F4;
    u8 b1F5;
    u8 b1F6;
    u8 pad1F7;
    u8 b1F8;
    u8 b1F9;
    u8 pad1FA[2];
    void* proj0;
    void* proj1;
    u8 b204;               // 0x204
    u8 pad205[3];
    BowShadowTex* shadowTex0;   // 0x208
    BowShadowTex* shadowTex1;  // 0x20C
    f32 f210;          // 0x210
    f32 f214;          // 0x214
};

class RPSysMiddleDB;

class RPSysMiddleDBGenInfo {
public:
    s32 mType;          // 0x00
    u16 mSize;          // 0x04
    s32 mGenderMask;    // 0x08
    s32 mAgeMask;       // 0x0C
    s32 mRaceMask;      // 0x10
    void* mpMiiManager; // 0x14

    RPSysMiddleDBGenInfo();
    virtual ~RPSysMiddleDBGenInfo();

    void SetType(s32 type) {
        mType = type;
    }
    void SetSize(u16 size) {
        mSize = size;
    }
};

class RPSysMiddleDB {
public:
    void* mpMiddleDB;   // 0x00
    void* mpRandomDB;   // 0x04
    u16 mSize;          // 0x08
    u16 mStoredNum;     // 0x0A
    u16 mCurrentIndex;  // 0x0C

    RPSysMiddleDB(const RPSysMiddleDBGenInfo* pGenInfo);
    virtual ~RPSysMiddleDB();

    u16 GetStoredNum() const {
        return mStoredNum;
    }
    void SetCurrentIndex(u16 idx) {
        mCurrentIndex = idx;
    }
};

class RPSysKokeshiLocation {
public:
    s32 mDataSource;          // 0x00
    u16 mIndex;               // 0x04
    RPSysMiddleDB* mpMiddleDB;  // 0x08

    RPSysKokeshiLocation();
    virtual ~RPSysKokeshiLocation();

    void SetDataSource(s32 src) {
        mDataSource = src;
    }
    void SetMiddleDB(RPSysMiddleDB* pMiddleDB) {
        mpMiddleDB = pMiddleDB;
    }
};

struct BowColor {
    u8 r, g, b, a;
};

class RPSysKokeshiGenInfo {
public:
    s32 mGenType;                   // 0x00
    u8 mPlayerNo;                   // 0x04
    RPSysKokeshiLocation mLocation; // 0x08
    u16 mBodyType;                  // 0x18
    u32 mHandType;                  // 0x1C
    u8 mViewNo;                     // 0x20
    u32 mTypeOption;                // 0x24
    u32 mBufferOption;              // 0x28
    u16 mIconWidth;                 // 0x2C
    u16 mIconHeight;                // 0x2E
    s32 mResolution;                // 0x30
    u32 mExprFlag;                  // 0x34
    s32 mIconMipMap;                // 0x38
    s32 mIconBGType;                // 0x3C
    BowColor mIconBGColor;          // 0x40
    s32 mIconView;                  // 0x44
    s32 mIconExpression;            // 0x48
    s32 mIconEdge;                  // 0x4C
    BowColor mIconEdgeColor;        // 0x50
    u16 mIconEdgeWidth;             // 0x54

    RPSysKokeshiGenInfo();
    virtual ~RPSysKokeshiGenInfo();

    void SetGenType(s32 type) {
        mGenType = type;
    }
    void SetPlayerNo(u8 no) {
        mPlayerNo = no;
    }
    void SetBodyType(u16 type) {
        mBodyType = type;
    }
    void SetHandType(u32 type) {
        mHandType = type;
    }
    void SetViewNo(u8 no) {
        mViewNo = no;
    }
    void SetBufferOption(u32 opt) {
        mBufferOption = opt;
    }
    void SetResolution(s32 res) {
        mResolution = res;
    }
    void SetExpressionFlag(u32 flag) {
        mExprFlag = flag;
    }
    void SetLocation(const RPSysKokeshiLocation& rLocation) {
        mLocation = rLocation;
    }
};

class RPSysKokeshiOverloadInfo {
public:
    u16 mClothesType;  // 0x00

    RPSysKokeshiOverloadInfo() {}
    virtual ~RPSysKokeshiOverloadInfo();

    void SetClothesType(u16 type) {
        mClothesType = type;
    }
};

class RPGrpModelAnm {
public:
    enum Anm {
        Anm_Chr = 0
    };

    u8 pad000[0x68];

    virtual void v08();
    virtual void v0C();
    virtual void SetAnm(int type, int idx, u16 handle, const char* pName, int x);  // 0x10
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void SetPlay(int on);  // 0x64

    void CreateBuffer(Anm anm, u16 num);
};

class RPGrpModelMaterial {
public:
    struct GenModeInfo {
        u8 numChans;      // 0x0
        u8 numTexGens;    // 0x1
        u8 numTevStages;  // 0x2
        u8 numIndStages;  // 0x3
        u8 cullMode;      // 0x4
    };

    void SetGenMode(const GenModeInfo& rInfo);
    void GetGenMode(GenModeInfo& rInfo);
};

class RPGrpModel {
public:
    u8 mViewNo;     // 0x00
    u8 mDrawScene;  // 0x01
    u8 mDrawGroup;  // 0x02
    u8 unk3;        // 0x03
    u8 unk4;        // 0x04
    u8 unk5[3];
    u16 mFlags;     // 0x08
    u16 unkA;
    u32 unkC;       // 0x0C
    u8 pad010[0x2C - 0x10];
    RPGrpModelAnm* mpModelAnm;          // 0x2C
    RPGrpModelMaterial** mppMaterials;  // 0x30
    u8 pad034[0x44 - 0x34];

    static RPGrpModel* Construct(u16 handle, int idx, u8 viewNo, u32 typeOption, u32 bufferOption);
    static RPGrpModel* Construct(u16 handle, const char* pName, u8 viewNo, u32 typeOption,
                                 u32 bufferOption);

    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void SetReverseCulling(bool reverse);  // 0x1C
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual u16 GetMaterialNum() const;  // 0x5C
};

// RP_DEBUG_STUB_1 / RPSysAvatar view (vptr at 0x0).
class BowAvatarBase {
public:
    virtual void v08();
    virtual void LoadResource(const RPSysKokeshiOverloadInfo* pOverloadInfo);  // 0x0C
    virtual void ApplyLightTexture(u8 drawScene);                              // 0x10
};

class RPSysKokeshi : public BowAvatarBase {
public:
    RPSysKokeshiGenInfo mGenInfo;            // 0x04
    RPSysKokeshiOverloadInfo mOverloadInfo;  // 0x60
    u8 pad068[0xA4 - 0x68];
    RPGrpModel* mpNigaoeModel;     // 0xA4
    RPGrpModel* mpBodyModel;       // 0xA8
    RPGrpModel* mpLeftHandModel;   // 0xAC
    RPGrpModel* mpRightHandModel;  // 0xB0

    explicit RPSysKokeshi(const RPSysKokeshiGenInfo* pGenInfo);

    const RPSysKokeshiGenInfo& GetGenInfo() const {
        return mGenInfo;
    }
};

class RPSysKokeshiManager {
public:
    static u16 GetOfficialDBValidNum();
};

struct BowGlobal730 {
    u8 pad000[0x90];
    void* x90;
};
extern BowGlobal730* lbl_804BF730;

void* operator new(u32 size);
void* operator new[](u32 size);

extern "C" {

void* memset(void*, int, u32);
void __ct__15RP_DEBUG_STUB_1Fv(void*);
void __ct__18IRPSysHostIOSocketFv(void*);
void __ct__Q23EGG13ShadowTextureFUsUsUs(void*, u16, u16, u16);
s32 ogws_fn_801F8E04(void*);
void ogws_fn_80320968(void*);
void ogws_fn_80320944(void*, s32, RPSysKokeshi*, RPSysKokeshi*);
void ogws_fn_803474E4(void*, RPSysKokeshi*, RPSysKokeshi*, s32);
void fn_804D5B28(void*, RPSysKokeshi*, RPSysKokeshi*);
void InitializeConfig__Q27Bowling25RPBowBackgroundNpcManagerFi(void*, s32);
void SetModelGroups__Q27Bowling25RPBowBackgroundNpcManagerFiPQ27Bowling13NpcModelGroupPQ27Bowling13NpcModelGroup(
    void*, s32, RPSysKokeshi*, RPSysKokeshi*);

extern u8 lbl_803C4018[];  // RPGrpShadowTexture vtable
extern void* lbl_803CA3B0[];  // IRPSysHostIOSocket member vtable (defined at file end)
extern void* lbl_806DE958[];  // scene object base vtable (defined at file end)
extern u8 lbl_803CA538[];  // lane manager vtable
extern u8 lbl_803CA714[];
extern u8 lbl_803CA8B0[];
extern u8 lbl_803CA8E8[];
extern u8 lbl_803CA9A0[];  // RPBowBackgroundNpcManager vtable

}  // extern "C"

// Local RPUtlRandom view: calc() stores then returns sSeed, so the new seed
// stays in a register between consecutive random calls.
class RPUtlRandom {
public:
    static u32 getU32() {
        return calc();
    }
    static u32 getU32(u32 max) {
        return max * getF32();
    }
    static f32 getF32() {
        return static_cast<f32>(
                   static_cast<u16>(RANDF_MAX & (calc() >> RANDF_SHIFT))) /
               static_cast<f32>(RANDF_MAX + 1);
    }

private:
    static u32 calc() {
        sSeed = sSeed * MULT + 1;
        return sSeed;
    }

    static const u32 MULT;
    static const u32 RANDF_MAX;
    static const u32 RANDF_SHIFT;
    static u32 sSeed;
};

// Draw context at 0x1EC (no constructor).
struct BowDrawCtx {
    u8 pad000[0xCC];
};

// Lane manager (0x130): scene object base + IRPSysHostIOSocket at 0x4.
struct BowLaneMgrObj {
    u8 b[0x130];
    BowLaneMgrObj() {
        __ct__15RP_DEBUG_STUB_1Fv(this);
        *(void**)b = lbl_806DE958;
        __ct__18IRPSysHostIOSocketFv(b + 4);
        *(void**)b = lbl_803CA538;
        *(void**)(b + 4) = lbl_803CA538 + 0x24;
    }
};

// Player lane NPC (0x78): base + host IO socket at 0x4, socket member at 0x30.
struct BowObj78 {
    u8 b[0x78];
    BowObj78() {
        __ct__15RP_DEBUG_STUB_1Fv(this);
        *(void**)b = lbl_806DE958;
        __ct__18IRPSysHostIOSocketFv(b + 4);
        *(void**)b = lbl_803CA8B0;
        *(void**)(b + 4) = lbl_803CA8B0 + 0x24;
        u8* m = b + 0x30;
        __ct__18IRPSysHostIOSocketFv(m);
        *(void**)m = lbl_803CA3B0;
    }
};

// Background lane NPC (0xA8): socket member at 0x5C.
struct BowObjA8 {
    u8 b[0xA8];
    BowObjA8() {
        __ct__15RP_DEBUG_STUB_1Fv(this);
        *(void**)b = lbl_803CA714;
        u8* m = b + 0x5C;
        __ct__18IRPSysHostIOSocketFv(m);
        *(void**)m = lbl_803CA3B0;
    }
};

// Bowling::RPBowBackgroundNpcManager (0x9C): socket member at 0x4C.
struct BowBgNpcMgr {
    u8 b[0x9C];
    BowBgNpcMgr() {
        __ct__15RP_DEBUG_STUB_1Fv(this);
        *(void**)b = lbl_806DE958;
        __ct__18IRPSysHostIOSocketFv(b + 4);
        *(void**)b = lbl_803CA9A0;
        *(void**)(b + 4) = lbl_803CA9A0 + 0x24;
        u8* m = b + 0x4C;
        __ct__18IRPSysHostIOSocketFv(m);
        *(void**)m = lbl_803CA3B0;
    }
};

struct BowObj4C {
    u8 b[0x4C];
    BowObj4C() {
        __ct__15RP_DEBUG_STUB_1Fv(this);
        *(void**)b = lbl_803CA8E8;
    }
};

struct BowShadowTexNew {
    u8 b[0x200];
    BowShadowTexNew(u16 size, u16 format, u16 num) {
        __ct__Q23EGG13ShadowTextureFUsUsUs(this, size, format, num);
        *(void**)((u8*)this + 0x14) = lbl_803C4018;
    }
};

extern "C" {

// Draw-path blur object returned from the draw path manager (offset 0x20):
// 8 bytes of non-polymorphic data, then the vptr.
struct BowDPBase {
    u8 pad000[0x08];
};

struct BowDPState {
    u8 pad000[0x19];
    u8 alpha;  // 0x19
    u8 pad01A[0x24 - 0x1A];
    s32 on;    // 0x24
};

struct BowDPObj : BowDPBase {
    virtual void v08();  // 0x08
    virtual void on();   // 0x0C
    virtual void off();  // 0x10
    BowDPState* state;   // 0x0C
};

class RPGrpShadowTexture;
class RPGrpDrawPathShadowTexture {
public:
    void SetTexture(u16 idx, RPGrpShadowTexture* pTexture);
};

struct BowDPMgr {
    u8 pad000[0x1C];
    RPGrpDrawPathShadowTexture* shadow;  // 0x1C
    BowDPObj* blur;  // 0x20
};

struct BowMdlMgr;
extern BowMdlMgr* spCurrent__17RPGrpModelManager;
BowDPMgr* GetDrawPathManager__17RPGrpModelManagerCFUc(BowMdlMgr*, u8);

void fn_804C7B60(void*) {}

void fn_804C7B64(BowSceneObjs* self, u32 mode, f32 alpha) {
    if (mode != 2) {
        for (s32 i = 0; i < 121; i++) {
            if (self->objs[i]) {
                self->objs[i]->v1C(0);
            }
        }
    } else {
        for (s32 i = 0; i < 121; i++) {
            if (self->objs[i]) {
                self->objs[i]->v1C(1);
                self->objs[i]->v20(0);
            }
        }
        if (mode == 2 && alpha < 0.95f) {
            self->objs[2]->v20(1);
            self->objs[12]->v20(1);
        }
        BowDPObj* blur = GetDrawPathManager__17RPGrpModelManagerCFUc(spCurrent__17RPGrpModelManager, 0)->blur;
        if (mode == 2 && alpha < 0.95f) {
            blur->on();
            blur->state->alpha = 255.0f * alpha;
            blur->state->on = 1;
        } else {
            blur->off();
            blur->state->alpha = 0;
        }
    }
}

void fn_804C7D10(void*) {}
void fn_804C7D14(void*) {}

void fn_804C7D18(BowSceneObjs* self) {
    for (s32 i = 0; i < 121; i++) {
        BowObj* o = self->objs[i];
        if (o) {
            o->v14();
        }
    }
}

void fn_804C7D78(void*) {}

void fn_80372C9C(void*, void*, int);

void fn_804C7D7C(BowSceneObjs* self, void* a, int b) {
    s32 i;
    if (self->b1F4) {
        f32 t = ((BowMtxObj*)self->objs[12])->GetPos().x / self->f210;
        if (t < -1.0f) {
            t = -1.0f;
        }
        if (t > 1.0f) {
            t = 1.0f;
        }
        BowVec3 dir(t * self->f214, -0.5f, 0.2f);
        self->shadowTex0->dir = dir;
    } else {
        BowVec3 dir(0.0f, -0.5f, 0.2f);
        self->shadowTex0->dir = dir;
    }
    self->shadowTex0->update();
    self->shadowTex1->update();
    fn_80372C9C(self->pad1EC, a, b);
    if (self->objs[0] && self->en[0]) {
        self->objs[0]->v10(self->pad1EC);
    }
    for (i = 0; i < 7 && self->en[3]; i++) {
        if (self->objs[11 + i]) {
            self->objs[11 + i]->v10(self->pad1EC);
        }
    }
    if (self->b1F6) {
        for (i = 0; i < 18 && self->en[2]; i++) {
            if (self->objs[18 + i]) {
                self->objs[18 + i]->v10(self->pad1EC);
            }
        }
        for (i = 0; i < 4 && self->en[2]; i++) {
            if (self->objs[36 + i]) {
                self->objs[36 + i]->v10(self->pad1EC);
            }
        }
        for (i = 0; i < 4 && self->en[7]; i++) {
            if (self->objs[111 + i]) {
                self->objs[111 + i]->v10(self->pad1EC);
            }
        }
        for (i = 0; i < 4 && self->en[2]; i++) {
            if (self->objs[115 + i]) {
                self->objs[115 + i]->v10(self->pad1EC);
            }
        }
    }
    if (self->b1F9 && self->en[4]) {
        if (self->b1F4) {
            if (self->objs[3]) {
                self->objs[3]->v10(self->pad1EC);
            }
        } else if (self->b1F5 && self->objs[4]) {
            for (i = 0; i < 7; i++) {
                self->objs[4 + i]->v10(self->pad1EC);
            }
        }
    }
    if (self->b1F8) {
        for (i = 0; i < 7 && self->en[5]; i++) {
            if (self->objs[40 + i]) {
                self->objs[40 + i]->v10(self->pad1EC);
            }
        }
    }
    if (self->en[6]) {
        for (i = 0; i < 64; i++) {
            if (self->objs[47 + i]) {
                self->objs[47 + i]->v10(self->pad1EC);
            }
        }
    }
    if (self->objs[2]) {
        self->objs[2]->v10(self->pad1EC);
    }
}

void fn_804C81CC(void*) {}

}  // extern "C"

namespace Bowling {
struct SomeUnkManager0;
}


class RPGrpLightManager {
public:
    void LoadScnLight(u16 handle, const char* pName, f32 frame, u32 x);
};

struct BowModelScene {
    u8 pad000[0x0C];
    RPGrpLightManager* lightMgr;  // 0x0C
};

struct BowMdlMgr {
    BowModelScene* scene;
};
extern "C" {
void fn_8025659C__15RPGrpModelSceneFP21RPGrpProjectionObject(void*, void*);
void fn_802565B4__15RPGrpModelSceneFP21RPGrpProjectionObject(void*, void*);
void __dt__15RP_DEBUG_STUB_1Fv(void*, s32);
void __dt__18IRPSysHostIOSocketFv(void*, s32);
void __dl__FPv(void*);
}

namespace Bowling {
// fn_804C81D0: forwards its arguments to fn_80372C9C on the member at 0x1EC.
void* fn_804C81D0(SomeUnkManager0* self, void* pObj, int val) {
    fn_80372C9C(((BowSceneObjs*)self)->pad1EC, pObj, val);
    return ((BowSceneObjs*)self)->pad1EC;
}
}  // namespace Bowling

struct BowLaneGfx2 {
    u8 pad000[0xAC];
    void* x_ac;  // 0xAC
    void* x_b0;  // 0xB0
};
struct BowLaneEnt2 {
    BowLaneGfx2* a;  // 0xD4 + 8*i
    BowLaneGfx2* b;
};
// Resort lane manager view (invented names).
struct BowLaneMgr2 {
    u8 pad000[0xD4];
    BowLaneEnt2 ent[4];  // 0xD4
    s32 flag[4];         // 0xF4
    u8 pad104[0x144 - 0x104];
    u8 flagB[4];         // 0x144
};
struct BowPairObj {
    void* pad0;
    struct BowPairHalf* a;  // 0x04
    struct BowPairHalf* b;  // 0x08
};
struct BowPairHalf {
    u8 pad000[0xB0];
    void* x_b0;
};
extern "C" {
void fn_8024DCA0(void*, int);
s16 fn_8027B258(void*, int);
int fn_8027B310(void*, int, int, int);

static inline BowPairObj* BowPairAt(BowSceneObjs* self, s32 k) {
    return (BowPairObj*)self->objs[k];
}

void fn_804C8404(BowSceneObjs* self, s32 idx) {
    s32 k = idx + 0x13;
    BowPairObj* o = BowPairAt(self, k);
    BowPairHalf* a = o->a;
    BowPairHalf* b = o->b;
    fn_8024DCA0(a->x_b0, 1);
    fn_8024DCA0(b->x_b0, 1);
}
}

extern "C" {

void fn_804C8204(BowSceneObjs* self) {
    for (s32 i = 0; i < 121; i++) {
        BowObj* o = self->objs[i];
        if (o) {
            o->v0C();
        }
    }
    self->b1F4 = 0;
    self->b1F5 = 0;
    self->b1F6 = 0;
    self->b1F8 = 1;
    self->b1F9 = 1;
}

void fn_804C8280(void*) {}

void fn_804C8458(BowSceneObjs* self, s32 idx, s32 flag) {
    BowLaneMgr2* mgr = (BowLaneMgr2*)self->objs[2];
    BowLaneGfx2* a = mgr->ent[idx].a;
    BowLaneGfx2* b = mgr->ent[idx].b;
    if (flag == 0) {
        fn_8024DCA0(a->x_b0, 1);
        fn_8024DCA0(b->x_b0, 1);
        fn_8024DCA0(b->x_ac, 1);
    } else {
        fn_8024DCA0(a->x_b0, 0);
        fn_8024DCA0(b->x_b0, 0);
        fn_8024DCA0(b->x_ac, 1);
    }
    mgr->flagB[idx] = flag;
}

void* fn_804C84F4(BowSceneObjs* self, s32 idx) {
    return ((BowLaneMgr2*)self->objs[2])->ent[idx].a;
}

s32 fn_804C8508(BowSceneObjs* self, s32 idx) {
    return ((BowLaneMgr2*)self->objs[2])->flag[idx];
}

int fn_804C851C(BowSceneObjs* self, s32 idx) {
    return fn_8027B258(((BowLaneMgr2*)self->objs[2])->ent[idx].a, 2) >= 3;
}

u16 fn_804C8568(BowSceneObjs* self, s32 idx) {
    return (u16)fn_8027B310(((BowLaneMgr2*)self->objs[2])->ent[idx].a, 5, 4, 0);
}

static inline int BowSum3(void* p) {
    u16 a = fn_8027B310(p, 5, 3, 0);
    u16 b = fn_8027B310(p, 5, 2, 0);
    return (u16)fn_8027B310(p, 5, 4, 0) + (b + a);
}

int fn_804C85A8(BowSceneObjs* self, s32 idx) {
    return BowSum3(((BowLaneMgr2*)self->objs[2])->ent[idx].a);
}

int fn_804C862C(BowSceneObjs* self, s32 idx, s32 mode) {
    if (mode == 1) {
        return 0;
    } else if (mode == 2) {
        return 1;
    }
    return fn_8027B258(((BowLaneMgr2*)self->objs[2])->ent[idx].a, 1) == 2;
}

int fn_804C8690(BowSceneObjs* self, s32 idx, s32 mode) {
    if (mode == 1) {
        return 0;
    } else if (mode == 2) {
        return 1;
    }
    return fn_8027B258(((BowLaneMgr2*)self->objs[2])->ent[idx].a, 0) != 2;
}

}  // extern "C"

extern "C" {

void ogws_fn_80316C04(BowSceneObjs* self, s32 flag) {
    self->b1F4 = flag;
    if ((u8)flag) {
        fn_8025659C__15RPGrpModelSceneFP21RPGrpProjectionObject(spCurrent__17RPGrpModelManager->scene, self->proj0);
        fn_802565B4__15RPGrpModelSceneFP21RPGrpProjectionObject(spCurrent__17RPGrpModelManager->scene, self->proj1);
    } else {
        fn_8025659C__15RPGrpModelSceneFP21RPGrpProjectionObject(spCurrent__17RPGrpModelManager->scene, self->proj1);
        fn_802565B4__15RPGrpModelSceneFP21RPGrpProjectionObject(spCurrent__17RPGrpModelManager->scene, self->proj0);
    }
}

}  // extern "C"

class RPGrpModelResManager {
public:
    enum Type {
        Type_ResFile = 0xC,
        Type_ResAnmChr = 0x10
    };

    static RPGrpModelResManager* spCurrent;

    u16 CreateData(Type type, void* pData, u32 x);
    void* GetPtr(Type type, u16 handle, const char* pName) const;
};

class RPGrpProjectionObject {
public:
    u8 pad000[0x1E8];

    RPGrpProjectionObject(u8 x);
    void LoadScnCamera(u16 handle, const char* pName, f32 frame);
};

class RPGrpShadowTexture {
public:
    void Replace(RPGrpModel* pModel, const char* pName, ...);
};

struct BowShadowParam {
    f32 value;
    u8 flag;
};

// Shadow texture fields written by the scene setup.
struct BowShadowTexData {
    u8 pad000[0x70];
    u16 flags;          // 0x70
    u8 alpha;           // 0x72
    u8 pad073;
    f32 x74;            // 0x74
    BowVec3 dir;        // 0x78
    u8 pad084[0xEC - 0x84];
    BowShadowParam param[2];  // 0xEC
};

extern void* lbl_804BF9A8;
extern u8 lbl_803CA430[];
// Bowling::RPBowActiveBall vtable at 0x803CA660 (inside lbl_803CA650 in the
// current symbols.txt; needs its own symbol).
extern u8 lbl_806DEAD0[];
extern u8 lbl_806DEA88[];
extern u8 lbl_806DEBB0[];
extern u8 lbl_806DEAF8[];
extern u8 lbl_806DEA40[];
extern u8 lbl_806DE9E0[];

extern "C" {
void* fn_804D93E4(void*, const char*);
void ogws_fn_8032ADF4(void*);
void ogws_fn_8032ADD8(void*, s32, RPGrpModel*, RPGrpModel*);
void ogws_fn_8031EF5C(void*, RPGrpModel*, RPGrpModel*, RPGrpModel*, RPGrpModel*, RPGrpModel*, RPGrpModel*,
                 RPGrpModel*, RPGrpModel*);
void ogws_fn_8031EF48(void*, s32, RPGrpModel*, RPGrpModel*);
void ogws_fn_80320930(void*, u16, u16, s32, RPGrpModel*);
void fn_804D5A18(void*, RPGrpModel*);
void fn_804D0D6C(void*, RPGrpModel*, RPGrpModel*);
void fn_804D08F4(void*, RPGrpModel*, RPGrpModel*);
void fn_804D1CD0(void*, RPGrpModel*, RPGrpModel*);
void SetMainModels__Q27Bowling20RPBowTrajectoryGuideFP10RPGrpModelP10RPGrpModel(void*, RPGrpModel*,
                                                                               RPGrpModel*);
void SetDotModel__Q27Bowling20RPBowTrajectoryGuideFUlP10RPGrpModel(void*, u32, RPGrpModel*);
void InitBallReturnRack__Q27Bowling19RPBowBallReturnRackFl(void*, s32);
void InitBallSlotResources__Q27Bowling19RPBowBallReturnRackFlP10RPGrpModelP10RPGrpModell(
    void*, s32, RPGrpModel*, RPGrpModel*, s32);
void SetBlurModels__Q27Bowling15RPBowMotionBlurFP10RPGrpModelP10RPGrpModelP10RPGrpModelP10RPGrpModelP10RPGrpModelP10RPGrpModel(
    void*, RPGrpModel*, RPGrpModel*, RPGrpModel*, RPGrpModel*, RPGrpModel*, RPGrpModel*);
}

// Bowling::RPBowActiveBall (0x88).
struct BowActiveBallNew {
    u8 b[0x80];
    BowShadowTex* shadow;  // 0x80
    s32 lane;              // 0x84
    BowActiveBallNew() {
        __ct__15RP_DEBUG_STUB_1Fv(this);
        *(void**)b = lbl_806DEAD0;
    }
};

// Lane field object (0x50).
struct BowFieldNew {
    u8 b[0x50];
    BowFieldNew() {
        __ct__15RP_DEBUG_STUB_1Fv(this);
        *(void**)b = lbl_803CA430;
    }
};

// Pin manager (0x2230).
struct BowPinMgrNew {
    u8 b[0x2230];
    BowPinMgrNew() {
        __ct__15RP_DEBUG_STUB_1Fv(this);
        *(void**)b = lbl_806DEA88;
        *(void**)(b + 4) = lbl_806DEA88 + 0x24;
    }
};

// Pin setter (0x3D8).
struct BowPinSetterNew {
    u8 b[0x3D0];
    BowShadowTex* shadow;  // 0x3D0
    s32 lane;              // 0x3D4
    BowPinSetterNew() {
        __ct__15RP_DEBUG_STUB_1Fv(this);
        *(void**)b = lbl_806DEA40;
        *(void**)(b + 4) = lbl_806DEA40 + 0x24;
    }
};

// Bowling::RPBowTrajectoryGuide (0x6C).
struct BowGuideNew {
    u8 b[0x6C];
    BowGuideNew() {
        __ct__15RP_DEBUG_STUB_1Fv(this);
        *(void**)b = lbl_806DE9E0;
    }
};

// Bowling::RPBowBallReturnRack (0xDC).
struct BowRackNew {
    u8 b[0xDC];
    BowRackNew() {
        __ct__15RP_DEBUG_STUB_1Fv(this);
        *(void**)b = lbl_806DE958;
        __ct__18IRPSysHostIOSocketFv(b + 4);
        *(void**)b = lbl_806DEAF8;
        *(void**)(b + 4) = lbl_806DEAF8 + 0x24;
    }
};

// Bowling::RPBowMotionBlur (0xB4).
struct BowBlurNew {
    u8 b[0xB4];
    BowBlurNew() {
        __ct__15RP_DEBUG_STUB_1Fv(this);
        *(void**)b = lbl_806DEBB0;
    }
};

struct BowNpcPair {
    u8 pad000[4];
    RPSysKokeshi* body;  // 0x4
    RPSysKokeshi* head;  // 0x8
};

struct BowLaneNpc {
    u8 pad000[8];
    RPSysKokeshi* body;  // 0x8
    RPSysKokeshi* head;  // 0xC
};

struct BowLaneKokeshi {
    RPSysKokeshi* body;  // 0x8C
    RPSysKokeshi* head;  // 0x90
};

struct BowLaneMgrData {
    u8 pad000[0x8C];
    BowLaneKokeshi ent[4];  // 0x8C
};

struct BowBgPair {
    RPSysKokeshi* body;  // 0x38
    RPSysKokeshi* head;  // 0x3C
};

struct BowBgNpcData {
    u8 pad000[0x38];
    BowBgPair pair[2];  // 0x38
};

struct BowBgLaneNpc {
    u8 pad000[4];
    RPSysKokeshi* body;  // 0x04
    RPSysKokeshi* head;  // 0x08
    u8 pad00c[0xA4 - 0xC];
    u8 reverse;          // 0xA4
};

static inline u16 BowCreateAnm(RPGrpModelResManager* resMgr, u16 handle, const char* pName) {
    return resMgr->CreateData(RPGrpModelResManager::Type_ResAnmChr,
                              resMgr->GetPtr(RPGrpModelResManager::Type_ResAnmChr, handle, pName), 0);
}

static inline void BowSetBodyReverse(BowBgLaneNpc* npc) {
    RPSysKokeshi* body = npc->body;
    RPSysKokeshi* head = npc->head;
    body->mpBodyModel->SetReverseCulling(true);
    head->mpBodyModel->SetReverseCulling(true);
}

enum BowCullMode {
    BOW_CULL_NONE,
    BOW_CULL_FRONT,
    BOW_CULL_BACK,
    BOW_CULL_ALL
};

static inline BowCullMode BowGetCullMode(RPGrpModelMaterial* mat) {
    RPGrpModelMaterial::GenModeInfo info;
    mat->GetGenMode(info);
    return (BowCullMode)info.cullMode;
}

static inline void BowSetCullMode(RPGrpModelMaterial* mat, BowCullMode mode) {
    RPGrpModelMaterial::GenModeInfo info;
    mat->GetGenMode(info);
    info.cullMode = mode;
    mat->SetGenMode(info);
}

// Swap front/back face culling of one material.
static inline void BowSwapCull(RPGrpModelMaterial* mat) {
    if (BowGetCullMode(mat) == BOW_CULL_BACK) {
        BowSetCullMode(mat, BOW_CULL_FRONT);
    } else if (BowGetCullMode(mat) == BOW_CULL_FRONT) {
        BowSetCullMode(mat, BOW_CULL_BACK);
    }
}

// Mirror model: draw priority 1 and swapped face culling. The material is
// passed straight to BowSwapCull (a nested-inline parameter), which colours it
// after the kokeshi model locals as in retail.
// MATCH-PENDING (R17): name inferred; material accessor. Its return temp is
// numbered after the kokeshi body/head accessor temps, which gives the mirror
// material retail's r29 in the kokeshi loops (ogws_fn_80316C7C 99.9 -> 100).
static inline RPGrpModelMaterial* BowGetMaterial(RPGrpModel* mdl, int i) {
    return mdl->mppMaterials[i];
}
static inline void BowSetupMirror(RPGrpModel* mdl) {
    mdl->unk3 = 1;
    mdl->unk4 = 1;
    for (int i = 0; i < mdl->GetMaterialNum(); i++) {
        BowSwapCull(BowGetMaterial(mdl, i));
    }
}

// MATCH-PENDING (R17): name inferred; hand-written operator new + inline ctor
// body. The local `b` is an inline-expansion variable created before the ball
// loop's BowSetupMirror locals, which gives the ball retail's register (r27);
// a plain `new BowActiveBallNew` temp is numbered after every inline expansion.
static inline BowActiveBallNew* BowNewBall() {
    BowActiveBallNew* b = (BowActiveBallNew*)::operator new(0x88);
    if (b) {
        __ct__15RP_DEBUG_STUB_1Fv(b);
        *(void**)b->b = lbl_806DEAD0;
    }
    return b;
}


// MATCH-PENDING (R17): names inferred; hand-written operator new + inline ctor
// body, as BowNewBall. The local `p` is an inline-expansion variable (numbered
// before every `new` temp), which gives the field retail's register (r18 below
// the string base and field91Res) and the rack its retail colouring.
// ogws_fn_80316C7C 99.4 -> 99.6.
static inline BowFieldNew* BowNewField() {
    BowFieldNew* p = (BowFieldNew*)::operator new(0x50);
    if (p) {
        __ct__15RP_DEBUG_STUB_1Fv(p);
        *(void**)p->b = lbl_803CA430;
    }
    return p;
}
static inline BowRackNew* BowNewRack() {
    BowRackNew* p = (BowRackNew*)::operator new(0xDC);
    if (p) {
        __ct__15RP_DEBUG_STUB_1Fv(p);
        *(void**)p->b = lbl_806DE958;
        __ct__18IRPSysHostIOSocketFv(p->b + 4);
        *(void**)p->b = lbl_806DEAF8;
        *(void**)(p->b + 4) = lbl_806DEAF8 + 0x24;
    }
    return p;
}
// MATCH-PENDING (R17): names inferred; head-kokeshi accessors for the four
// kokeshi holder types. Reading `head` through an inline return value makes it
// an @-temp, which gives the kokeshi loops retail's head register (r27) and
// mirror material/offset colouring; the real accessors are not identified.
// ogws_fn_80316C7C harness 150 -> 101 lines.
static inline RPSysKokeshi* BowKokHead(BowLaneKokeshi* e) { return e->head; }
static inline RPSysKokeshi* BowKokHead(BowLaneNpc* e) { return e->head; }
static inline RPSysKokeshi* BowKokHead(BowBgPair* e) { return e->head; }
static inline RPSysKokeshi* BowKokHead(BowBgLaneNpc* e) { return e->head; }
// MATCH-PENDING (R17): names inferred; body-kokeshi accessors, read before the
// head accessor. Inline return temps are numbered in source order after the
// nested-inline parameters; body (first) colours last, then head, then the
// mirror material (BowGetMaterial), as retail r26/r27/r29 in all four kokeshi
// loops. The real accessors are not identified.
static inline RPSysKokeshi* BowKokBody(BowLaneKokeshi* e) { return e->body; }
static inline RPSysKokeshi* BowKokBody(BowLaneNpc* e) { return e->body; }
static inline RPSysKokeshi* BowKokBody(BowBgPair* e) { return e->body; }
static inline RPSysKokeshi* BowKokBody(BowBgLaneNpc* e) { return e->body; }

// Mirror kokeshi: all three body models mirrored, face model flagged.
static inline void BowSetupMirrorKokeshi(RPSysKokeshi* kok) {
    RPGrpModel* mdl;
    for (int j = 0; j < 3; j++) {
        if (j == 0) {
            mdl = kok->mpBodyModel;
        }
        if (j == 1) {
            mdl = kok->mpLeftHandModel;
        }
        if (j == 2) {
            mdl = kok->mpRightHandModel;
        }
        BowSetupMirror(mdl);
    }
    kok->mpNigaoeModel->unk3 = 1;
    kok->mpNigaoeModel->unk4 = 1;
    kok->mpNigaoeModel->unkC |= 0x20;
}



extern "C" {

void BowScene_Print(const char*);

// Placeholder for a function absent from the DOL (inferred: dead-stripped by
// the linker; name and body are NOT known). It held a local table of the three
// Mii database labels ("表ＤＢ", "裏ＤＢ", "ＣＰＵ ＤＢ"); only its .rodata
// initializer and pooled strings survive, ahead of ogws_fn_80316C7C's.
void BowScene_StrippedDbNames(s32 db) {
    const char* dbNames[3] = {"\x95\x5C\x82\x63\x82\x61", "\x97\xA0\x82\x63\x82\x61",
                              "\x82\x62\x82\x6F\x82\x74\x20\x82\x63\x82\x61"};
    BowScene_Print(dbNames[db]);
}

// ogws_fn_80316C7C: loads the bowling scene resources and builds every scene
// object's models.
void fn_804C86F4(BowSceneObjs* self) {
    RPGrpModelResManager* resMgr = RPGrpModelResManager::spCurrent;

    u16 hScene = resMgr->CreateData(RPGrpModelResManager::Type_ResFile,
                                    fn_804D93E4(lbl_804BF9A8, "G3D/bwg_field_rsca.brres"), 0);
    spCurrent__17RPGrpModelManager->scene->lightMgr->LoadScnLight(hScene, "RPScene", 0.0f, -1);
    self->proj0 = new RPGrpProjectionObject(0xF);
    ((RPGrpProjectionObject*)self->proj0)->LoadScnCamera(hScene, "RPScene", 0.0f);
    fn_802565B4__15RPGrpModelSceneFP21RPGrpProjectionObject(spCurrent__17RPGrpModelManager->scene,
                                                           self->proj0);
    hScene = resMgr->CreateData(RPGrpModelResManager::Type_ResFile,
                                fn_804D93E4(lbl_804BF9A8, "G3D/bwg_field_91_rsca.brres"), 0);
    self->proj1 = new RPGrpProjectionObject(0xF);
    ((RPGrpProjectionObject*)self->proj1)->LoadScnCamera(hScene, "RPScene", 0.0f);

    u16 hBall = resMgr->CreateData(RPGrpModelResManager::Type_ResFile,
                                   fn_804D93E4(lbl_804BF9A8, "G3D/bwg_ball.brres"), 0);
    u16 hBallPro = resMgr->CreateData(RPGrpModelResManager::Type_ResFile,
                                      fn_804D93E4(lbl_804BF9A8, "G3D/bwg_ball_pro.brres"), 0);
    u16 hShadow = resMgr->CreateData(RPGrpModelResManager::Type_ResFile,
                                     fn_804D93E4(lbl_804BF9A8, "G3D/bwg_ava_shadow.brres"), 0);

    const char* ballNames[5] = {"bwg_ball_blue", "bwg_ball_pink", "bwg_ball_green", "bwg_ball_yellow",
                                "bwg_ball_blue"};
    const char* ballMirrorNames[5] = {"bwg_ball_blue_mirror", "bwg_ball_pink_mirror",
                                      "bwg_ball_green_mirror", "bwg_ball_yellow_mirror",
                                      "bwg_ball_blue_mirror"};
    const char* proNames[5] = {"bwg_ball_blue_pro", "bwg_ball_pink_pro", "bwg_ball_green_pro",
                               "bwg_ball_yellow_pro", "bwg_ball_blue_pro"};
    const char* proMirrorNames[5] = {"bwg_ball_blue_pro_mirror", "bwg_ball_pink_pro_mirror",
                                     "bwg_ball_green_pro_mirror", "bwg_ball_yellow_pro_mirror",
                                     "bwg_ball_blue_pro_mirror"};

    for (s32 i = 0; i < 7; i++) {
        BowActiveBallNew* ball = BowNewBall();
        self->objs[11 + i] = (BowObj*)ball;
        ogws_fn_8032ADF4(ball);
        for (s32 j = 0; j < 8; j++) {
            RPGrpModel* mdl;
            RPGrpModel* mirror;
            if (j < 4) {
                mdl = RPGrpModel::Construct(hBall, ballNames[j % 4], 1, 0, 0x118);
                mirror = RPGrpModel::Construct(hBall, ballMirrorNames[j % 4], 1, 0, 0x118);
            } else {
                mdl = RPGrpModel::Construct(hBallPro, proNames[j % 4], 1, 0, 0x118);
                mirror = RPGrpModel::Construct(hBallPro, proMirrorNames[j % 4], 1, 0, 0x118);
            }
            BowSetupMirror(mirror);
            ogws_fn_8032ADD8(ball, j, mdl, mirror);
            ball->shadow = self->shadowTex0;
            ball->lane = i;
            mdl->unk3 = 0xF;
            mdl->unk4 = 0xF;
        }
    }

    u16 hPin = resMgr->CreateData(RPGrpModelResManager::Type_ResFile,
                                  fn_804D93E4(lbl_804BF9A8, "G3D/bwg_Pin.brres"), 0);
    BowFieldNew* field = BowNewField();
    self->objs[0] = (BowObj*)field;
    void* fieldRes = fn_804D93E4(lbl_804BF9A8, "G3D/bwg_field.brres");
    void* field91Res = fn_804D93E4(lbl_804BF9A8, "G3D/bwg_field_91.brres");
    u16 hField = resMgr->CreateData(RPGrpModelResManager::Type_ResFile, fieldRes, 0);
    u16 hField91 = resMgr->CreateData(RPGrpModelResManager::Type_ResFile, field91Res, 0);
    RPGrpModel* front = RPGrpModel::Construct(hField, "bwg_field_front", 1, 0, 0);
    RPGrpModel* pinArea = RPGrpModel::Construct(hField, "bwg_field_pin", 1, 0, 0);
    RPGrpModel* field91 = RPGrpModel::Construct(hField91, "bwg_field_91", 1, 0, 0);
    RPGrpModel* wallL = RPGrpModel::Construct(hField91, "bwg_wall_L", 1, 0, 0);
    RPGrpModel* wallR = RPGrpModel::Construct(hField91, "bwg_wall_R", 1, 0, 0);
    RPGrpModel* wallLMirror = RPGrpModel::Construct(hField91, "bwg_wall_L_mirror", 1, 0, 0x10);
    RPGrpModel* wallRMirror = RPGrpModel::Construct(hField91, "bwg_wall_R_mirror", 1, 0, 0x10);
    RPGrpModel* fieldMdl = RPGrpModel::Construct(hField, "bwg_field", 1, 0, 0);
    BowSetupMirror(wallLMirror);
    BowSetupMirror(wallRMirror);
    ogws_fn_8031EF5C(field, front, field91, pinArea, fieldMdl, wallL, wallR, wallLMirror, wallRMirror);
    for (s32 i = 0; i < 4; i++) {
        RPGrpModel* etc = RPGrpModel::Construct(hField, "lane_alpha_etc", 1, 0, 0);
        RPGrpModel* alpha = RPGrpModel::Construct(hField, "lane_alpha", 1, 0, 0);
        ogws_fn_8031EF48(field, i, etc, alpha);
        etc->unk3 = 0;
        etc->unk4 = 0;
        alpha->unk3 = 0;
        alpha->unk4 = 0;
    }
    front->unk3 = 2;
    front->unk4 = 2;
    fieldMdl->unk3 = 2;
    fieldMdl->unk4 = 2;
    field91->unk3 = 2;
    field91->unk4 = 2;
    pinArea->unk4 = 3;

    ((RPGrpShadowTexture*)self->shadowTex0)->Replace(front, "projection_1");
    ((RPGrpShadowTexture*)self->shadowTex0)->Replace(fieldMdl, "projection_1");
    ((RPGrpShadowTexture*)self->shadowTex0)->Replace(field91, "projection_1");
    ((RPGrpShadowTexture*)self->shadowTex0)->Replace(wallL, "projection_1");
    ((RPGrpShadowTexture*)self->shadowTex0)->Replace(wallR, "projection_1");
    ((BowShadowTexData*)self->shadowTex0)->dir = BowVec3(0.0f, -0.5f, 0.2f);
    ((BowShadowTexData*)self->shadowTex0)->flags |= 2;
    ((BowShadowTexData*)self->shadowTex0)->alpha = 0x40;
    ((BowShadowTexData*)self->shadowTex0)->x74 = 2.0f;
    BowShadowParam param;
    for (s32 i = 0; i < 2; i++) {
        BowShadowTexData* d = (BowShadowTexData*)self->shadowTex0;
        param = d->param[i];
        param.value = 3.0f;
        ((BowShadowTexData*)self->shadowTex0)->param[i] = param;
    }
    ((RPGrpShadowTexture*)self->shadowTex1)->Replace(front, "projection_2");
    ((RPGrpShadowTexture*)self->shadowTex1)->Replace(fieldMdl, "projection_2");
    ((BowShadowTexData*)self->shadowTex1)->dir = BowVec3(0.0f, -1.0f, 0.0f);
    ((BowShadowTexData*)self->shadowTex1)->flags |= 2;
    ((BowShadowTexData*)self->shadowTex1)->alpha = 0x78;
    ((BowShadowTexData*)self->shadowTex1)->x74 = 2.0f;
    for (s32 i = 0; i < 2; i++) {
        BowShadowTexData* d = (BowShadowTexData*)self->shadowTex1;
        param = d->param[i];
        param.value = 3.0f;
        ((BowShadowTexData*)self->shadowTex1)->param[i] = param;
    }

    u16 hAnim = resMgr->CreateData(RPGrpModelResManager::Type_ResFile,
                                   fn_804D93E4(lbl_804BF9A8, "G3D/bwg_avatar_anim.brres"), 0);
    BowLaneMgrData* lanes = (BowLaneMgrData*)self->objs[1];
    for (s32 i = 0; i < 4; i++) {
        RPSysKokeshi* body = BowKokBody(&lanes->ent[i]);
        RPSysKokeshi* head = BowKokHead(&lanes->ent[i]);
        RPSysKokeshiOverloadInfo ov;
        ov.SetClothesType(4);
        body->LoadResource(&ov);
        body->ApplyLightTexture(0);
        head->LoadResource(&body->mOverloadInfo);
        head->ApplyLightTexture(0);
        BowSetupMirrorKokeshi(head);
        RPSysKokeshi* kok;
        for (s32 k = 0; k < 2; k++) {
            kok = k == 0 ? body : head;
            kok->mpBodyModel->mpModelAnm->CreateBuffer(RPGrpModelAnm::Anm_Chr, 6);
            kok->mpBodyModel->mpModelAnm->SetAnm(0, 3, hAnim, "bwg_wait_legR", 0);
            kok->mpBodyModel->mpModelAnm->SetAnm(0, 4, hAnim, "bwg_throwR_tmp", 0);
            kok->mpBodyModel->mpModelAnm->SetAnm(0, 5, hAnim, "bwg_wait_armR", 0);
            kok->mpBodyModel->mpModelAnm->SetAnm(0, 0, hAnim, "bwg_walkR", 0);
            kok->mpBodyModel->mpModelAnm->SetAnm(0, 1, hAnim, "bwg_throw1R", 0);
            kok->mpBodyModel->mpModelAnm->SetAnm(0, 2, hAnim, "bwg_throw2R", 0);
        }
    }
    u16 hMove = BowCreateAnm(resMgr, hAnim, "bwg_moveR");
    u16 hWaitMove = BowCreateAnm(resMgr, hAnim, "bwg_wait_moveR");
    ogws_fn_80320930(lanes, hMove, hWaitMove, 2, RPGrpModel::Construct(hShadow, 0, 1, 0, 0x100));

    for (s32 i = 0; i < 4; i++) {
        BowLaneNpc* npc = (BowLaneNpc*)self->objs[36 + i];
        RPSysKokeshi* body = BowKokBody(npc);
        RPSysKokeshi* head = BowKokHead(npc);
        RPSysKokeshiOverloadInfo ov;
        ov.SetClothesType(4);
        body->LoadResource(&ov);
        body->ApplyLightTexture(0);
        head->LoadResource(&body->mOverloadInfo);
        head->ApplyLightTexture(0);
        BowSetupMirrorKokeshi(head);
        head->mpNigaoeModel->SetReverseCulling(true);
        RPSysKokeshi* kok;
        for (s32 k = 0; k < 2; k++) {
            kok = k == 0 ? body : head;
            kok->mpBodyModel->mpModelAnm->CreateBuffer(RPGrpModelAnm::Anm_Chr, 1);
            kok->mpBodyModel->mpModelAnm->SetAnm(0, 0, hAnim, "bwg_A0_wait3R", 0);
            kok->mpBodyModel->mpModelAnm->SetPlay(1);
        }
    }

    if (self->b204) {
        for (s32 m = 0; m < 4; m++) {
            BowBgNpcData* bg = (BowBgNpcData*)self->objs[115 + m];
            for (s32 n = 0; n < 2; n++) {
                RPSysKokeshi* body = BowKokBody(&bg->pair[n]);
                RPSysKokeshi* head = BowKokHead(&bg->pair[n]);
                body->LoadResource(NULL);
                body->ApplyLightTexture(0);
                head->LoadResource(&body->mOverloadInfo);
                head->ApplyLightTexture(0);
                BowSetupMirrorKokeshi(head);
                head->mpNigaoeModel->SetReverseCulling(true);
                RPSysKokeshi* kok;
                for (s32 k = 0; k < 2; k++) {
                    kok = k == 0 ? body : head;
                    kok->mpBodyModel->mpModelAnm->CreateBuffer(RPGrpModelAnm::Anm_Chr, 2);
                    kok->mpBodyModel->mpModelAnm->SetAnm(0, 0, hAnim, "bwg_A0_wait3R", 0);
                    kok->mpBodyModel->mpModelAnm->SetAnm(0, 1, hAnim, "bwg_A0_frontR", 0);
                    kok->mpBodyModel->mpModelAnm->SetPlay(1);
                }
            }
        }
        for (s32 m = 0; m < 18; m++) {
            BowBgLaneNpc* npc = (BowBgLaneNpc*)self->objs[18 + m];
            RPSysKokeshi* body = BowKokBody(npc);
            RPSysKokeshi* head = BowKokHead(npc);
            RPGrpModel* shadow = RPGrpModel::Construct(hShadow, 0, 1, 0, 0x100);
            body->LoadResource(NULL);
            body->ApplyLightTexture(0);
            head->LoadResource(&body->mOverloadInfo);
            head->ApplyLightTexture(0);
            BowSetupMirrorKokeshi(head);
            fn_804D5A18(npc, shadow);
            head->mpNigaoeModel->SetReverseCulling(true);
            RPSysKokeshi* kok;
            for (s32 k = 0; k < 2; k++) {
                kok = k == 0 ? body : head;
                kok->mpBodyModel->mpModelAnm->CreateBuffer(RPGrpModelAnm::Anm_Chr, 9);
                kok->mpBodyModel->mpModelAnm->SetAnm(0, 0, hAnim, "bwg_A0_walkR", 0);
                kok->mpBodyModel->mpModelAnm->SetAnm(0, 1, hAnim, "bwg_A0_waitR", 0);
                kok->mpBodyModel->mpModelAnm->SetAnm(0, 2, hAnim, "bwg_A0_throwR", 0);
                kok->mpBodyModel->mpModelAnm->SetAnm(0, 3, hAnim, "bwg_A0_wait2R", 0);
                kok->mpBodyModel->mpModelAnm->SetAnm(0, 4, hAnim, "bwg_A0_UturnR", 0);
                kok->mpBodyModel->mpModelAnm->SetAnm(0, 5, hAnim, "bwg_A0_returnR", 0);
                kok->mpBodyModel->mpModelAnm->SetAnm(0, 6, hAnim, "bwg_A0_wait3R", 0);
                kok->mpBodyModel->mpModelAnm->SetAnm(0, 7, hAnim, "bwg_A0_frontR", 0);
                kok->mpBodyModel->mpModelAnm->SetAnm(0, 8, hAnim, "bwg_A0_happyR", 0);
                kok->mpBodyModel->mpModelAnm->SetPlay(1);
            }
            s32 row = m / 3;
            if (row == 2 || row == 3) {
                BowSetBodyReverse((BowBgLaneNpc*)self->objs[18 + m]);
                npc->reverse = 0;
            } else {
                npc->reverse = 1;
            }
        }
    }

    BowPinMgrNew* pins = new BowPinMgrNew;
    self->objs[3] = (BowObj*)pins;
    RPGrpModel* pinMdl = RPGrpModel::Construct(hPin, "bwg_pin_438_91", 1, 0, 0x10);
    RPGrpModel* pinMirror = RPGrpModel::Construct(hPin, "bwg_pin_286_91", 1, 0, 0x10);
    fn_804D0D6C(pins, pinMdl, pinMirror);
    BowSetupMirror(pinMirror);

    for (s32 i = 0; i < 7; i++) {
        BowPinSetterNew* setter = new BowPinSetterNew;
        self->objs[4 + i] = (BowObj*)setter;
        RPGrpModel* mdl;
        RPGrpModel* mirror;
        if (i == 0) {
            mdl = RPGrpModel::Construct(hPin, "bwg_pin_866_10", 1, 0, 0);
            mirror = RPGrpModel::Construct(hPin, "bwg_pin_286_10", 1, 0, 0);
        }
        if (i == 1 || i == 2) {
            mdl = RPGrpModel::Construct(hPin, "bwg_pin_438_10", 1, 0, 0);
            mirror = RPGrpModel::Construct(hPin, "bwg_pin_74_10", 1, 0, 0);
        }
        if (i == 3 || i == 4) {
            mdl = RPGrpModel::Construct(hPin, "bwg_pin_166_10", 1, 0, 0);
            mirror = RPGrpModel::Construct(hPin, "bwg_pin_74_10", 1, 0, 0);
        }
        if (i == 5 || i == 6) {
            mdl = RPGrpModel::Construct(hPin, "bwg_pin_74_10", 1, 0, 0);
            mirror = NULL;
        }
        fn_804D08F4(setter, mdl, mirror);
        setter->shadow = self->shadowTex1;
        setter->lane = i;
        if (mirror) {
            BowSetupMirror(mirror);
        }
    }

    for (s32 i = 0; i < 7; i++) {
        void* conveyor = self->objs[40 + i];
        u16 hConv = resMgr->CreateData(RPGrpModelResManager::Type_ResFile,
                                       fn_804D93E4(lbl_804BF9A8, "G3D/bwg_conveyer.brres"), 0);
        RPGrpModel* mdl = RPGrpModel::Construct(hConv, "pin_conveyer", 1, 0, 0x10);
        RPGrpModel* mirror = RPGrpModel::Construct(hConv, "pin_conveyer", 1, 0, 0x10);
        for (s32 k = 0; k < 2; k++) {
            RPGrpModel* m = k == 0 ? mdl : mirror;
            m->mpModelAnm->CreateBuffer(RPGrpModelAnm::Anm_Chr, 1);
            m->mpModelAnm->SetAnm(0, 0, hConv, "pin_conveyer", 0);
        }
        fn_804D1CD0(conveyor, mdl, mirror);
        BowSetupMirror(mirror);
    }

    u16 hThrow = resMgr->CreateData(RPGrpModelResManager::Type_ResFile,
                                    fn_804D93E4(lbl_804BF9A8, "G3D/bwg_throwline.brres"), 0);
    BowGuideNew* guide = new BowGuideNew;
    self->objs[2] = (BowObj*)guide;
    RPGrpModel* arrow0 = RPGrpModel::Construct(hThrow, "bwg_arrow_00", 1, 0, 0);
    SetMainModels__Q27Bowling20RPBowTrajectoryGuideFP10RPGrpModelP10RPGrpModel(
        guide, RPGrpModel::Construct(hThrow, "bwg_arrow_01", 1, 0, 0), arrow0);
    for (s32 i = 0; i < 16; i++) {
        RPGrpModel* dot = RPGrpModel::Construct(hThrow, "bwg_throwline", 1, 0, 0);
        SetDotModel__Q27Bowling20RPBowTrajectoryGuideFUlP10RPGrpModel(guide, i, dot);
        dot->unk3 = 0xE;
        dot->unk4 = 0xE;
    }

    for (s32 i = 0; i < 4; i++) {
        BowRackNew* rack = BowNewRack();
        self->objs[111 + i] = (BowObj*)rack;
        InitBallReturnRack__Q27Bowling19RPBowBallReturnRackFl(rack, i);
        for (s32 j = 0; j < 4; j++) {
            u32 color = RPUtlRandom::getU32() % 4;
            RPGrpModel* mdl = RPGrpModel::Construct(hBall, ballNames[color], 1, 0, 0x118);
            RPGrpModel* mirror = RPGrpModel::Construct(hBall, ballMirrorNames[color], 1, 0, 0x118);
            BowSetupMirror(mirror);
            InitBallSlotResources__Q27Bowling19RPBowBallReturnRackFlP10RPGrpModelP10RPGrpModell(
                rack, j, mdl, mirror, color);
        }
    }

    for (s32 i = 0; i < 64; i++) {
        BowBlurNew* blur = new BowBlurNew;
        self->objs[47 + i] = (BowObj*)blur;
        u16 hGate = resMgr->CreateData(RPGrpModelResManager::Type_ResFile,
                                       fn_804D93E4(lbl_804BF9A8, "G3D/bwg_gate.brres"), 0);
        RPGrpModel* frameL = RPGrpModel::Construct(hGate, "bwg_gate_frame_L", 1, 0, 0x10);
        RPGrpModel* gate = RPGrpModel::Construct(hGate, "bwg_gate", 1, 0, 0x10);
        RPGrpModel* frameR = RPGrpModel::Construct(hGate, "bwg_gate_frame_R", 1, 0, 0x10);
        RPGrpModel* frameLMirror = RPGrpModel::Construct(hGate, "bwg_gate_frame_L", 1, 0, 0x10);
        RPGrpModel* gateMirror = RPGrpModel::Construct(hGate, "bwg_gate", 1, 0, 0x10);
        RPGrpModel* frameRMirror = RPGrpModel::Construct(hGate, "bwg_gate_frame_R", 1, 0, 0x10);
        SetBlurModels__Q27Bowling15RPBowMotionBlurFP10RPGrpModelP10RPGrpModelP10RPGrpModelP10RPGrpModelP10RPGrpModelP10RPGrpModel(
            blur, frameL, gate, frameR, frameLMirror, gateMirror, frameRMirror);
        BowSetupMirror(frameLMirror);
        BowSetupMirror(gateMirror);
        BowSetupMirror(frameRMirror);
    }
}


void* fn_804CA014(void* p, s32 del) {
    if (p) {
        if (del > 0) {
            __dl__FPv(p);
        }
    }
    return p;
}

void fn_804CA054(void*) {}

}  // extern "C"


// MATCH-PENDING (R17): name inferred; an accessor for the NPC middle DB held at
// +0x08 of the Mii group object. Reading it through an inline return value makes
// npcDb an @-temp (coloured with the other level-1 values) instead of a named
// local; the real accessor/class is not identified. ogws_fn_80318EB0 99.1 -> 99.3.
static inline RPSysMiddleDB* BowGetNpcDb(void* mgr) { return ((RPSysMiddleDB**)mgr)[2]; }

// MATCH-PENDING (R17): names inferred; hand-written operator new + inline ctor
// bodies (as BowNewBall). The local `p` (and the socket-member local `m`,
// declared first in BowNewLaneNpc) are inline-expansion variables, numbered
// before every `new` temp and before the NPC DB accessor: the bg manager gets
// retail's r20 (coloured before npcDb r19), the lane manager r23 and the lane
// NPC r24/r25. Plain `new` temps are numbered later. ogws_fn_80318EB0 99.3 -> 99.9.
static inline BowBgNpcMgr* BowNewBgNpcMgr() {
    BowBgNpcMgr* p = (BowBgNpcMgr*)::operator new(0x9C);
    if (p) {
        __ct__15RP_DEBUG_STUB_1Fv(p);
        *(void**)p->b = lbl_806DE958;
        __ct__18IRPSysHostIOSocketFv(p->b + 4);
        *(void**)p->b = lbl_803CA9A0;
        *(void**)(p->b + 4) = lbl_803CA9A0 + 0x24;
        u8* m = p->b + 0x4C;
        __ct__18IRPSysHostIOSocketFv(m);
        *(void**)m = lbl_803CA3B0;
    }
    return p;
}
static inline BowObj78* BowNewLaneNpc() {
    u8* m;
    BowObj78* p = (BowObj78*)::operator new(0x78);
    if (p) {
        __ct__15RP_DEBUG_STUB_1Fv(p);
        *(void**)p->b = lbl_806DE958;
        __ct__18IRPSysHostIOSocketFv(p->b + 4);
        *(void**)p->b = lbl_803CA8B0;
        *(void**)(p->b + 4) = lbl_803CA8B0 + 0x24;
        m = p->b + 0x30;
        __ct__18IRPSysHostIOSocketFv(m);
        *(void**)m = lbl_803CA3B0;
    }
    return p;
}
static inline BowLaneMgrObj* BowNewLaneMgr() {
    BowLaneMgrObj* p = (BowLaneMgrObj*)::operator new(0x130);
    if (p) {
        __ct__15RP_DEBUG_STUB_1Fv(p);
        *(void**)p->b = lbl_806DE958;
        __ct__18IRPSysHostIOSocketFv(p->b + 4);
        *(void**)p->b = lbl_803CA538;
        *(void**)(p->b + 4) = lbl_803CA538 + 0x24;
    }
    return p;
}

// MATCH-PENDING (R17): invented one-field holder for the official Mii DB
// pointer. IRO_ScalarizeClassDataMembers turns officialDb.p into an optimizer
// @temp numbered after the random loop's getU32 return temp and before the
// LICM temps (MULT/SHIFT/MAX), so it gets retail's r17; a named pointer local
// ranks below every @temp (r24). The real source shape is not identified.
// ogws_fn_80318EB0 99.9 -> 100.
struct BowDbRef {
    RPSysMiddleDB* p;
};

extern "C" {

// ogws_fn_80318EB0: scene object manager setup. Creates the Mii databases, the
// player/NPC kokeshi models and the per-lane objects.
void fn_804CA0BC(BowSceneObjs* self, u32, u8 bgNpc, s32 nPlayers) {
    s32 counts[3];
    self->b204 = bgNpc;
    memset(self->objs, 0, sizeof(self->objs));

    RPSysMiddleDB* db;
    BowDbRef officialDb;
    RPSysMiddleDB* npcDb;
    {
        RPSysMiddleDBGenInfo info;
        info.SetType(0);
        info.SetSize(0x22);
        db = new RPSysMiddleDB(&info);
        counts[1] = db->GetStoredNum();
    }
    counts[0] = RPSysKokeshiManager::GetOfficialDBValidNum();
    if (counts[0] != 0) {
        RPSysMiddleDBGenInfo info;
        info.SetType(3);
        info.SetSize(counts[0] + 4);
        officialDb.p = new RPSysMiddleDB(&info);
    } else {
        officialDb.p = 0;
    }

    void* mgr = lbl_804BF730->x90;
    npcDb = BowGetNpcDb(mgr);
    counts[2] = ogws_fn_801F8E04(lbl_804BF730->x90);
    u8* order = new u8[counts[2]];
    for (s32 i = 0; i < counts[2]; i++) {
        order[i] = i;
    }
    for (s32 i = 0; i < 100; i++) {
        s32 x = RPUtlRandom::getU32(counts[2]);
        s32 y = RPUtlRandom::getU32(counts[2]);
        if (x >= 0 && x < counts[2] && y >= 0 && y < counts[2]) {
            u8 t = order[x];
            order[x] = order[y];
            order[y] = t;
        }
    }

    RPSysKokeshiLocation locs[3];
    locs[0].SetDataSource(0);
    locs[0].SetMiddleDB(officialDb.p);
    locs[1].SetDataSource(7);
    locs[1].SetMiddleDB(db);
    locs[2].SetDataSource(7);
    locs[2].SetMiddleDB(npcDb);

    self->pad1EC = new BowDrawCtx;
    BowLaneMgrObj* lanes = BowNewLaneMgr();
    self->objs[1] = (BowObj*)lanes;
    ogws_fn_80320968(lanes);

    for (s32 i = 0; i < 4; i++) {
        RPSysKokeshiGenInfo info;
        if (i < nPlayers) {
            info.SetGenType(0);
            info.SetPlayerNo(i);
        } else {
            for (s32 j = 0; j < 3; j++) {
                if (counts[j] > 0) {
                    info.SetGenType(1);
                    info.SetLocation(locs[j]);
                    if (j == 2) {
                        npcDb->SetCurrentIndex(order[counts[j] - 1]);
                    }
                    counts[j]--;
                    break;
                }
            }
        }
        info.SetViewNo(1);
        info.SetBufferOption(0x10);
        info.SetBodyType(2);
        info.SetHandType(1);
        info.SetExpressionFlag(0x21);
        RPSysKokeshi* body = new RPSysKokeshi(&info);
        info = body->GetGenInfo();
        info.SetGenType(2);
        info.SetExpressionFlag(1);
        RPSysKokeshi* head = new RPSysKokeshi(&info);
        ogws_fn_80320944(lanes, i, body, head);
        info.SetBodyType(0);
        info.SetExpressionFlag(1);
        info.SetResolution(0x40);
        RPSysKokeshi* npcBody = new RPSysKokeshi(&info);
        info = npcBody->GetGenInfo();
        info.SetExpressionFlag(1);
        info.SetResolution(0x40);
        RPSysKokeshi* npcHead = new RPSysKokeshi(&info);
        BowObj78* npc = BowNewLaneNpc();
        ogws_fn_803474E4(npc, npcBody, npcHead, i);
        self->objs[36 + i] = (BowObj*)npc;
    }

    if (self->b204) {
        for (s32 k = 0; k < 18; k++) {
            BowObjA8* obj = new BowObjA8;
            self->objs[18 + k] = (BowObj*)obj;
            RPSysKokeshiGenInfo info;
            for (s32 j = 1; j < 3; j++) {
                if (counts[j] > 0) {
                    info.SetGenType(1);
                    info.SetLocation(locs[j]);
                    if (j == 2) {
                        npcDb->SetCurrentIndex(order[counts[j] - 1]);
                    }
                    counts[j]--;
                    break;
                }
            }
            info.SetBodyType(0);
            info.SetHandType(1);
            info.SetExpressionFlag(3);
            info.SetViewNo(1);
            info.SetBufferOption(0x10);
            RPSysKokeshi* body = new RPSysKokeshi(&info);
            info = body->GetGenInfo();
            info.SetGenType(2);
            info.SetResolution(0x40);
            info.SetExpressionFlag(1);
            RPSysKokeshi* head = new RPSysKokeshi(&info);
            fn_804D5B28(obj, body, head);
            if (k == 5) {
                for (s32 m = 0; m < 4; m++) {
                    BowBgNpcMgr* bg = BowNewBgNpcMgr();
                    self->objs[115 + m] = (BowObj*)bg;
                    InitializeConfig__Q27Bowling25RPBowBackgroundNpcManagerFi(bg, m);
                    for (s32 n = 0; n < 2; n++) {
                        RPSysKokeshiGenInfo info;
                        for (s32 j = 1; j < 3; j++) {
                if (counts[j] > 0) {
                    info.SetGenType(1);
                    info.SetLocation(locs[j]);
                    if (j == 2) {
                        npcDb->SetCurrentIndex(order[counts[j] - 1]);
                    }
                    counts[j]--;
                    break;
                }
            }
                        info.SetBodyType(0);
                        info.SetHandType(1);
                        info.SetViewNo(1);
                        info.SetBufferOption(0x10);
                        info.SetResolution(0x40);
                        RPSysKokeshi* body = new RPSysKokeshi(&info);
                        info = body->GetGenInfo();
                        info.SetGenType(2);
                        RPSysKokeshi* head = new RPSysKokeshi(&info);
                        SetModelGroups__Q27Bowling25RPBowBackgroundNpcManagerFiPQ27Bowling13NpcModelGroupPQ27Bowling13NpcModelGroup(bg, n, body, head);
                    }
                }
            }
        }
    }

    for (s32 i = 0; i < 7; i++) {
        self->objs[40 + i] = (BowObj*)new BowObj4C;
    }
    self->en[0] = 1;
    self->en[1] = 1;
    self->en[2] = 1;
    self->en[3] = 1;
    self->en[4] = 1;
    self->en[5] = 1;
    self->en[6] = 1;
    self->en[7] = 1;
    self->f210 = 4.0f;
    self->f214 = 0.07f;
    BowShadowTex* tex;
    tex = (BowShadowTex*)new BowShadowTexNew(0x100, 1, 1);
    self->shadowTex0 = tex;
    tex = (BowShadowTex*)new BowShadowTexNew(0x18E, 1, 1);
    self->shadowTex1 = tex;
    self->shadowTex0->init();
    self->shadowTex1->init();
    tex = self->shadowTex0;
    GetDrawPathManager__17RPGrpModelManagerCFUc(spCurrent__17RPGrpModelManager, 0)
        ->shadow->SetTexture(0, (RPGrpShadowTexture*)tex);
    tex = self->shadowTex1;
    self = (BowSceneObjs*)tex;
    GetDrawPathManager__17RPGrpModelManagerCFUc(spCurrent__17RPGrpModelManager, 0)
        ->shadow->SetTexture(1, (RPGrpShadowTexture*)self);
}

struct BowObjA058 {
    void* x0;
    BowVec3 v4;
    s32 x10;
    f32 f14;
};
extern "C" void __ct__Q34nw4r4math4VEC3Fv(void*);
void fn_8038DB64(void*, f32);

BowObjA058* fn_804CA058(BowObjA058* self) {
    __ct__Q34nw4r4math4VEC3Fv(&self->v4);
    fn_8038DB64(self, 1000.0f);
    self->x0 = 0;
    self->f14 = 0.05f;
    return self;
}

void fn_804CA0A8(void** p) {
    *p = (void*)lbl_806DE958;
}

void fn_804CA0B8(void*) {}


// MATCH-PENDING (R17): hand vtable arrays stand in for the compiler vtables of
// the socket-derived helper (dtor fn_804CA058) and the scene object base class
// (dtor fn_804CA014), whose classes are not modelled here.
void ListenPropertyEvent__18IRPSysHostIOSocketFv();
void GenMessage__18IRPSysHostIOSocketFv();

void* lbl_803CA3B0[5] = {
    0, 0, (void*)fn_804CA058, (void*)ListenPropertyEvent__18IRPSysHostIOSocketFv,
    (void*)GenMessage__18IRPSysHostIOSocketFv,
};
void* lbl_806DE958[10] = {
    0, 0, (void*)fn_804CA014, (void*)fn_804C8280, (void*)fn_804C81CC, (void*)fn_804C7D78,
    (void*)fn_804C7B60, (void*)fn_804C7D14, (void*)fn_804C7D10, 0,
};

}  // extern "C"
