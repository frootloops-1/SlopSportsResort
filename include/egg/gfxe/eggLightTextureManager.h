#ifndef EGG_GFXE_LIGHT_TEXTURE_MANAGER_H
#define EGG_GFXE_LIGHT_TEXTURE_MANAGER_H
#include <egg/types_egg.h>

#include <egg/core.h>
#include <egg/prim/eggAssert.h>
#include <egg/gfxe/eggScreen.h>

namespace EGG {

// Forward declarations
class LightManager;
class LightTexture;
class LightObject;

class LightTextureManager : IBinary<LightTextureManager> {
public:
    struct BinData {
        u16 texNum; // at 0x10
        char unk12[0x20 - 0x12];
    };

public:
    LightTextureManager(const LightManager* pManager);

    virtual void SetBinaryInner(const IBinary::Bin& rBinary); // at 0x8
    virtual void GetBinaryInner(IBinary::Bin* pBinary) const; // at 0xC

    virtual const char* GetBinaryType() const; // at 0x10

    virtual u32 GetBinarySize() const; // at 0x14
    virtual u8 GetVersion() const; // at 0x18

    u16 createTexture(const char* pName);
    u16 replaceModelTexture(int, ModelEx*) const;
    int getTextureIndex(const char* pName) const;

    void correctLightObject();
    void frameReset();
    void drawAndCaptureTexture(LightManager*, const Screen::DataEfb&, f32, f32,
                               f32, f32);

    bool IsEnable() const {
        return mFlags & cFlag_4;
    }

    void SetEnable(bool enable) {
        if (enable) {
            mFlags |= cFlag_4;
        } else {
            mFlags = mFlags & ~cFlag_4;
        }
    }

    LightTexture* getTexture(u16 index) const {
        EGG_ASSERT_LINE(112, index < mTexNum);
        return mppLightTextures[index];
    }

    bool isEnableClearWorkSpace() const {
        return mFlags & cFlag_ClearWorkSpace;
    }

    u32 getMax() const {
        return LIGHT_TEX_MAX;
    }

private:
    enum {
        cFlag_ClearWorkSpace = 1 << 3,
        cFlag_4 = 1 << 4,
        cFlag_5 = 1 << 5,
        cFlag_6 = 1 << 6,
    };

    static const u8 VERSION = 0;

    static const int LIGHT_TEX_MAX = 32;
    static const int LIGHT_OBJ_MAX = 32;

private:
    u8 mFlags;                          // at 0x4
    u16 mTexNum;                        // at 0x6
    LightTexture** mppLightTextures;    // at 0x8
    const LightManager* mpLightManager; // at 0xC
    u32 mDrawFlags;                     // at 0x10
    u16 mLightObjNum;                   // at 0x14
    LightObj** mppLightObjs;            // at 0x18
};

} // namespace EGG

#endif
