#ifndef EGG_CORE_IBINARY_H
#define EGG_CORE_IBINARY_H
#include <egg/types_egg.h>

#include <egg/prim.h>

namespace EGG {

template <typename T> class IBinary {
public:
#pragma pack(push, 1)
    struct BinHeader {
        u8 magic[4]; // at 0x0
        u32 size;      // at 0x4
        u8 version;    // at 0x8
        u8 unk9[0x10 - 0x9];
    };

    struct Bin {
        BinHeader header;
        typename T::BinData data;
    };
#pragma pack(pop)

    virtual void SetBinaryInner(const Bin& rBinary) = 0; // at 0x8
    virtual void GetBinaryInner(Bin* pBinary) const = 0; // at 0xC

    virtual const char* GetBinaryType() const = 0; // at 0x10
    virtual u32 GetBinarySize() const {
        return sizeof(T::Bin);
    }; // at 0x14

    virtual u8 GetVersion() const = 0; // at 0x18

#pragma push
#pragma dont_inline on
    void SetBinary(const void* bin);
#pragma pop

#pragma push
#pragma dont_inline on
    void GetBinary(void* bin) const {
#line 105
        EGG_ASSERT(bin);
        Bin* pBinary = (Bin*)bin;

        pBinary->header.version = GetVersion();
        pBinary->header.size = GetBinarySize();

        for (int i = 0; i < (int)sizeof(pBinary->header.magic); i++) {
            pBinary->header.magic[i] = GetBinaryType()[i];
        }

        GetBinaryInner(pBinary);
    }
#pragma pop

    static void SetBinaryExtension(const char* pName) {
#line 46
        EGG_ASSERT(pName != NULL);
        spExtension = pName;
    }

private:
    static const char* spExtension;
};

} // namespace EGG

#endif
