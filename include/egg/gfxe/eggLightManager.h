#ifndef EGG_GFXE_LIGHT_MANAGER_H
#define EGG_GFXE_LIGHT_MANAGER_H
#include <egg/types_egg.h>

#include <egg/core/eggIBinary.h>
#include <egg/prim.h>

#include <nw4r/g3d.h>

#include <revolution/GX.h>

namespace EGG {

//! Ambient light entry (inferred layout)
struct AmbientObj {
    GXColor mColor;    // at 0x0
    const char* mName; // at 0x4
};

class LightManager : IBinary<LightManager> {
public:
    //! Ambient light entry in the binary (inferred)
    struct AmbBin {
        GXColor color; // at 0x0
        u8 pad[4];     // at 0x4
    };

    struct BinData {
        u16 lightNum;               // at 0x10
        u16 ambientNum;             // at 0x12
        GXColor color;              // at 0x14
        u8 UNK_0x18[0x28 - 0x18];   // at 0x18
        u8 lights[0x50];            // at 0x28 (LightObject::Bin[lightNum])
        // AmbBin ambients[ambientNum] follows lights[lightNum]
    };

public:
    LightManager(u32 lightNum, u32 ambientNum, u8 viewNum);
    virtual ~LightManager() {} // at 0x1C
    virtual void SetBinaryInner(const IBinary::Bin&); // at 0x8
    virtual void GetBinaryInner(IBinary::Bin*) const; // at 0xC
    virtual const char* GetBinaryType() const;        // at 0x10
    virtual u32 GetBinarySize() const {
        // sizeof(Bin) + (lightNum - 1) * sizeof(LightObject::Bin) +
        // ambientNum * sizeof(AmbBin)
        return 0x78 + (m_binLightNum - 1) * 0x50 + m_binAmbientNum * 8;
    } // at 0x14
    virtual u8 GetVersion() const {
        return 2;
    }                          // at 0x18

    void Reset();
    // Name and body inferred (not in the symbol map; stripped from main.dol)
    void SetBinaryNum(u16 lightNum, u16 ambientNum);
    void Calc(nw4r::g3d::ScnRoot*);
    void CalcView(const nw4r::math::MTX34&, u8, nw4r::g3d::ScnRoot*);

    void LoadObjIndxGX() const;
    void LoadLightSetGD(int, u32*, u32*, u32*, u32*, GXColor*) const;
    void DoneDraw();

    void LoadScnLightInner(nw4r::g3d::ResAnmScn, f32, u32);

    void CopyToG3D_World(nw4r::g3d::ScnRoot*) const;
    void CopyToG3D_View(nw4r::g3d::ScnRoot*, const nw4r::math::MTX34&) const;

    LightObj* GetLightObj(u16 index) const {
#line 157
        EGG_ASSERT(index < GetNum());
        return m_ppLightSet[index];
    }

    LightObj* GetLightObj(u16 index) {
#line 166
        EGG_ASSERT(index < GetNum());
        return m_ppLightSet[index];
    }

    u16 GetNum() const {
        return m_numLight;
    }
    u16 GetAmbientNum() const {
        return m_numAmbient;
    }
    AmbientObj& GetAmbient(int idx) const {
#line 174
        EGG_ASSERT(0 <= idx && idx < GetAmbientNum());
        return m_pAmbientSet[idx];
    }
    //! Accessor name inferred
    AmbientObj* GetAmbientSet() const {
        return m_pAmbientSet;
    }
    u8 GetCurrentView() const {
        return m_currentView;
    }
    LightTextureManager* GetLightTextureManager() const {
        return m_pLightTextureManager;
    }

private:
    enum {
        cFlag_CalcDone = 1 << 2,
        cFlag_CalcViewDone = 1 << 3,
        cFlag_UseScnLightSet = 1 << 4,
    };

private:
    // Resort layout (ctor fn_801AF5D0, DoneDraw 0x801AFCE0, LoadScnLightInner
    // fn_801AFD0C); differs from Wii Sports.
    u8 m_numLight;                               // at 0x4
    u8 m_numAmbient;                             // at 0x5
    u8 m_binLightNum;                            // at 0x6
    u8 m_binAmbientNum;                          // at 0x7
    LightObj** m_ppLightSet;                     // at 0x8 (Resort: LightObject[], stride 0xA4)
    AmbientObj* m_pAmbientSet;                   // at 0xC (Resort stride 0xC)
    GXLightObj* m_pObjSet;                       // at 0x10
    LightTextureManager* m_pLightTextureManager; // at 0x14
    u32 mUnk18;                                  // at 0x18
    u8 m_viewNum;                                // at 0x1C
    u8 m_currentView;                            // at 0x1D
    u16 m_flags;                                 // at 0x1E
    nw4r::g3d::ResAnmScn m_scn;                  // at 0x20
    s16 m_lightSetRef;                           // at 0x24
};

} // namespace EGG

#endif
