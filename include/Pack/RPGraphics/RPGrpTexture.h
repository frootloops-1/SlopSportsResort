#ifndef RP_GRAPHICS_TEXTURE_H
#define RP_GRAPHICS_TEXTURE_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpModelResManager.h>

#include <egg/gfxe.h>

#include <revolution/GX.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpCaptureTexture;

/**
 * @brief GPU texture wrapper
 */
class RPGrpTexture {
private:
    // Resort layout (ctors 0x8025A190/0x8025A200/0x8025A260, load 0x8025A0F8;
    // RPSysKokeshiManager::CreateTexture 0x80246324 allocates 0x34). There
    // is no vtable: the ctors store no vptr.

    //! Bit 0: mTlutObj is valid and is loaded with the texture
    u8 mFlags; // at 0x0
    //! GX texture object
    GXTexObj mTexObj; // at 0x4
    //! GX TLUT object
    GXTlutObj mTlutObj; // at 0x24
    //! TLUT memory slot (GXTlut)
    u32 mTlutName; // at 0x30

public:
    /**
     * @brief Constructor
     *
     * @param pCpuTexture CPU texture
     */
    explicit RPGrpTexture(const EGG::CpuTexture* pCpuTexture);

    /**
     * @brief Constructor
     *
     * @param pResTIMG Texture image resource
     */
    explicit RPGrpTexture(const EGG::ResTIMG* pResTIMG);

    /**
     * @brief Constructor
     *
     * @param pCapTexture Capture texture
     */
    explicit RPGrpTexture(const RPGrpCaptureTexture* pCapTexture);

    /**
     * @brief Constructor
     *
     * @param handle Resource file handle
     * @param pName Texture name
     */
    RPGrpTexture(RPGrpHandle handle, const char* pName);

    /**
     * @brief Destructor
     */
    ~RPGrpTexture() {}

    /**
     * @brief Accesses the underlying GX texture object
     */
    const GXTexObj& GetTexObj() const {
        return mTexObj;
    }
};

//! @}

#endif
