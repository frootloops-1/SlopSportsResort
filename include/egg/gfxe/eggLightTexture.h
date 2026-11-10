#ifndef EGG_GFXE_LIGHT_TEXTURE_H
#define EGG_GFXE_LIGHT_TEXTURE_H
#include "eggCapTexture.h"
#include "eggIBinary.h"
#include "eggScreen.h"
#include "types_egg.h"

namespace EGG {

// Forward declarations
class LightObject;
class LightTextureManager;

class LightTexture : public CapTexture, public IBinary<LightTexture> {
public:
    // Layout inferred from Set/GetBinaryInner and GetBinarySize
    struct LightData {
        f32 value;  // at 0x0
        u8 pattern; // at 0x4
        u8 pad[3];
    };

    struct BinData {
        u16 lightNum;        // at 0x10
        u16 pad12;           // at 0x12
        char name[0x20];     // at 0x14
        u8 drawType;         // at 0x34
        u8 pad35[3];         // at 0x35
        u32 lightMask;       // at 0x38
        LightData lights[1]; // at 0x3C
    };

    // Draw status (names from assert strings)
    enum {
        cDrawStatus_None,
        cDrawStatus_Drawing,
        cDrawStatus_Drawn,
    };

    enum {
        cPttrn_Max = 10,
    };

    struct Setting {
        u8 mStatus;     // at 0x0 (0x78)
        u8 mStageNum;   // at 0x1 (0x79, inferred)
        u8 mTexMapBase; // at 0x2 (0x7A, inferred)
        u16 mLightCnt;  // at 0x4 (0x7C, inferred)
        u16 mPosX;      // at 0x6 (0x7E)
        u16 mPosY;      // at 0x8 (0x80)
    };

public:
    static void initialize(u16 textureSize, Heap* pHeap);
    static void initDrawSetting(u16 x, u16 y, u16 width, u16 height);
    static void getDrawSetting(u16*, u16*, u16*, u16*, u16);

    LightTexture(u16 index, const char* pName,
                 const LightTextureManager* pManager);
    virtual ~LightTexture();  // at 0x8
    virtual void configure(); // at 0xC

    // Declaration order (GetVersion first, Size before Type) reproduces the
    // original vtable layout; see the local IBinary copy in eggLightTexture.cpp.
    virtual u8 GetVersion() const;
    virtual void SetBinaryInner(const Bin&);
    virtual void GetBinaryInner(Bin*) const;
    virtual u32 GetBinarySize() const;
    virtual const char* GetBinaryType() const;

    void draw();
    void addLight(const LightObject& rLight);
    void capture(bool clearColor);

    const char* getName() const {
        return mName;
    }

    void setLightValue(u16 lightID, f32 value) {
#line 218
        EGG_ASSERT(lightID < mLightNum);
        mpEffectScale[lightID] = value;
    }

    f32 getLightValue(u16 lightID) const {
#line 226
        EGG_ASSERT(lightID < mLightNum);
        return mpEffectScale[lightID];
    }

    void setLightPattern(u16 lightID, int pattern) {
#line 234
        EGG_ASSERT(lightID < mLightNum);
        mpPttrn[lightID] = pattern;
    }

    int getLightPattern(u16 lightID) const {
#line 242
        EGG_ASSERT(lightID < mLightNum);
        return mpPttrn[lightID];
    }

    static CpuTexture* getPatternTexture(int pat) {
#line 282
        EGG_ASSERT(pat < cPttrn_Max);
        return spPatternSet[pat];
    }

    static CpuTexture* getNormalEnvironment() {
        return spNormalEnvironment;
    }

    void setDrawType(int type) {
        mDrawType = type;
    }

    u32 getLightMask() const {
        return mLightMaskLo | (mLightMaskHi << 16);
    }

public:
    static const int MAX_NAME_LEN = 32;

    s8 mTexScale;                         // at 0x30 (inferred)
    u16 mLightNum;                        // at 0x32
    f32 FLOAT_0x34;                       // at 0x34
    f32 FLOAT_0x38;                       // at 0x38
    f32 FLOAT_0x3C;                       // at 0x3C
    u16 mLightMaskLo;                     // at 0x40
    u16 mLightMaskHi;                     // at 0x42
    u16 mIndex;                           // at 0x44
    int mDrawType;                        // at 0x48
    f32* mpEffectScale;                   // at 0x4C 
    int* mpPttrn;                         // at 0x50
    char mName[MAX_NAME_LEN];             // at 0x54
    const LightTextureManager* mpManager; // at 0x74
    Setting mSetting;                     // at 0x78

    static u16 sTextureSize;
    static u16 sDrawWidth;
    static u16 sDrawHeight;
    static u16 sDrawPosX;
    static u16 sDrawPosY;
    static u16 sTexWidth;
    static u16 sTexHeight;
    static u16 sDrawNumX;
    static u16 sDrawNumY;
    static CpuTexture* spNormalEnvironment;
    static CpuTexture* spPatternSet[cPttrn_Max];
};

} // namespace EGG

#endif
