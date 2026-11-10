#ifndef EGG_GFXE_CAP_TEXTURE_H
#define EGG_GFXE_CAP_TEXTURE_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggCpuTexture.h>

#include <revolution/GX.h>

namespace EGG {

class CapTexture : public CpuTexture {
public:
    // Resort: the vertical filter is copied as a 7-byte aggregate
    // (lwz/lhz/lbz in configure 0x801A5138 and RPGrpView 0x80255050).
    // The type name is not from a symbol.
    struct VFilter {
        u8 coef[GX_VFILTER_SZ];
    };

public:
    CapTexture() {}
    CapTexture(u16 width, u16 height, GXTexFmt format)
        : CpuTexture(width, height, format) {}

    // Resort: vtable 0x806B4580 has two slots (dtor, configure 0x801A5138);
    // there is no CapTexture::load
    virtual void configure(); // at 0xC

    // Resort: 0x801A5194
    void capture(u16 x, u16 y, bool mipmap = false, int format = -1);

    void setClearColor(const GXColor& rColor) {
        mClearColor = rColor;
    }
    void setClearZ(u32 clearZ) {
        mClearZ = clearZ;
    }

    void setVFilterBlur() {
        enableVFilter();
        mVFilter = VFILTER_BLUR;
    }
    void setVFilterOff() {
        mVFilter = VFILTER_OFF;
    }

    bool checkColorUpdate() const {
        return testCapFlag(cFlag_ColorUpdate);
    }
    void enableColorUpdate() {
        setCapFlag(cFlag_ColorUpdate);
    }
    void disableColorUpdate() {
        clearCapFlag(cFlag_ColorUpdate);
    }

    bool checkAlphaUpdate() const {
        return testCapFlag(cFlag_AlphaUpdate);
    }
    void enableAlphaUpdate() {
        setCapFlag(cFlag_AlphaUpdate);
    }
    void disableAlphaUpdate() {
        clearCapFlag(cFlag_AlphaUpdate);
    }

    bool checkZBufferUpdate() const {
        return testCapFlag(cFlag_ZBufferUpdate);
    }
    void enableZBufferUpdate() {
        setCapFlag(cFlag_ZBufferUpdate);
    }
    void disableZBufferUpdate() {
        clearCapFlag(cFlag_ZBufferUpdate);
    }

    bool checkVFilterEnable() const {
        return testCapFlag(cFlag_VFilterEnable);
    }
    void enableVFilter() {
        setCapFlag(cFlag_VFilterEnable);
    }
    void disableVFilter() {
        clearCapFlag(cFlag_VFilterEnable);
    }

    bool checkPixModeSync() const {
        return testCapFlag(cFlag_PixModeSync);
    }
    void enablePixModeSync() {
        setCapFlag(cFlag_PixModeSync);
    }
    void disablePixModeSync() {
        clearCapFlag(cFlag_PixModeSync);
    }

    // Resort: inlined in RPGrpRenderer 0x80254BC8 (flag 0x20)
    void enableInvalidateTex() {
        setCapFlag(cFlag_InvalidateTex);
    }

private:
    // Resort: separate flag byte at 0x18 (capture 0x801A5194)
    enum {
        cFlag_ColorUpdate = 1 << 0,
        cFlag_AlphaUpdate = 1 << 1,
        cFlag_ZBufferUpdate = 1 << 2,
        cFlag_VFilterEnable = 1 << 3,
        cFlag_PixModeSync = 1 << 4,
        cFlag_InvalidateTex = 1 << 5,
    };

    void setCapFlag(u8 flag) {
        mCapFlags |= flag;
    }
    void clearCapFlag(u8 flag) {
        mCapFlags &= ~flag;
    }
    bool testCapFlag(u8 flag) const {
        return (mCapFlags & flag) ? true : false;
    }

private:
    // Resort layout (configure 0x801A5138, capture 0x801A5194)
    u8 mCapFlags;        // at 0x18
    GXColor mClearColor; // at 0x19
    u32 mClearZ;         // at 0x20
    VFilter mVFilter;    // at 0x24

    static const u8 SAMPLE_PATTERN_OFF[12][2];
    static const VFilter VFILTER_BLUR;
    static const VFilter VFILTER_OFF;
};

} // namespace EGG

#endif
