#ifndef RP_GRAPHICS_MODEL_MISC_H
#define RP_GRAPHICS_MODEL_MISC_H
#include <Pack/types_pack.h>

#include <egg/core.h>

//! @addtogroup rp_graphics
//! @{

/**
 * @brief Model material miscellaneous settings
 */
class RPGrpModelMisc : public EGG::IBinary<RPGrpModelMisc> {
public:
    virtual ~RPGrpModelMisc(); // at 0x1C

    /**
     * @brief Material target
     */
    struct MatTarget {
        char name[32]; // at 0x0
        bool unk20;    // at 0x20
        f32 unk24;     // at 0x24
    };

    /**
     * @brief Main binary file structure
     */
    struct BinData {
        u16 targetNum;       // at 0x10
        MatTarget targets[]; // at 0x14
    };

    /**
     * @brief Deserializes this object from a binary file
     *
     * @param rBinary Binary file contents
     */
    virtual void SetBinaryInner(const Bin& rBinary) override; // at 0x8

    /**
     * @brief Serializes this object to a binary file
     *
     * @param[out] pBinary Binary file contents
     */
    virtual void GetBinaryInner(Bin* pBinary) const override; // at 0xC

    /**
     * @brief Gets the binary signature of this object
     */
    virtual const char* GetBinaryType() const override;

    /**
     * @brief Gets the binary version of this object
     */
    virtual u8 GetVersion() const override;

private:
    //! Version of this file's specification
    static const u8 VERSION = 0;
};

//! @}

#endif
