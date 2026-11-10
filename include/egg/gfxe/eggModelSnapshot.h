#ifndef EGG_GFXE_MODEL_SNAPSHOT_H
#define EGG_GFXE_MODEL_SNAPSHOT_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggCapTexture.h>

namespace EGG {

// Forward declarations
class ModelEx;

class ModelSnapshot : public CapTexture {
public:
    ModelSnapshot(u16 width, u16 height, GXTexFmt format, u16 mdlMax);

    virtual void InitList();  // at 0x18
    virtual void ResetList(); // at 0x1C

    void AddModelEx(ModelEx* pModel, f32 adjust = 1.0f);
    void GatherModel(f32 adjust = 1.0f);

    // Resort: both found by direct calls from RPGrpShadowTexture
    // (0x80257BC8, 0x80257C0C); real names unknown
    int Unk_801B54FC(ModelEx* pModel); // index of pModel in list, or -1
    bool Unk_801B51FC(ModelEx* pModel);
    void SetMdlUnk9(ModelEx* pModel, bool flag) {
        int idx = Unk_801B54FC(pModel);
        m_mdlList[idx].mUnk9 = flag;
    }

protected:
    struct ModelBind {
        ModelEx* pModel; // at 0x0
        f32 adjust;      // at 0x4
        bool useMat;     // at 0x8
        u8 mUnk9;        // at 0x9 (reset to 0xFF by 0x801B5138)
    };

protected:
    // Resort layout: ctor 0x801B4F7C, InitList 0x801B50B4 (list = new
    // ModelBind[m_mdlMax] at 0x58), reset 0x801B5138
    u16 m_mdlMax; // at 0x2C
    u16 m_width;  // at 0x2E
    u16 m_height; // at 0x30
    u16 m_mdlNum; // at 0x32
    u8 m_flags;   // at 0x34
    f32 mUnk38;
    f32 mUnk3C;
    f32 mUnk40;
    f32 mUnk44;
    f32 mUnk48;
    f32 mUnk4C;
    f32 mUnk50;
    f32 mUnk54;
    ModelBind* m_mdlList; // at 0x58
    f32 mUnk5C;
    f32 mUnk60;
    f32 mUnk64;
    f32 mUnk68;
    f32 mUnk6C;

protected:
    enum {
        cFlag_1 = 1 << 1,
    };
};

} // namespace EGG

#endif
