#ifndef RP_GRAPHICS_SHADOW_TEXTURE_H
#define RP_GRAPHICS_SHADOW_TEXTURE_H
#include <Pack/types_pack.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

class RPGrpModel;

// Placeholder for the second model type accepted by the AddModel overloads
// (ModelEx pointer at 0x14); real class unknown.
struct RPGrpShadowSrc {
    char unk0[0x14];
    EGG::ModelEx* mpModelEx; // at 0x14
};

class RPGrpShadowTexture : public EGG::ShadowTexture {
public:
    /**
     * @brief Constructor
     *
     * @param size Texture size (width/height)
     * @param format Texture format
     * @param mdlNum Maximum number of scene models to gather
     */
    RPGrpShadowTexture(u16 size, int format, u16 mdlNum)
        : EGG::ShadowTexture(size, format, mdlNum) {}

    /**
     * @brief Destructor
     */
    virtual ~RPGrpShadowTexture() override {} // at 0x8

    /**
     * @brief Replaces a texture on the specified model
     *
     * @param pModel Target model
     * @param pName Texture name (format string)
     * @param ... Format string arguments
     */
    void Replace(RPGrpModel* pModel, const char* pName, ...);

    /**
     * @brief Adds a new model to the shadow texture
     *
     * @param pModel Model
     * @param density Model density
     */
    void AddModel(RPGrpModel* pModel, f32 density);

    /**
     * @brief Adds a new model with materials to the shadow texture
     *
     * @param pModel Model
     * @param density Model density
     */
    void AddModelUseMaterial(RPGrpModel* pModel, f32 density);

    void AddModel(RPGrpShadowSrc* pModel, f32 density);
    void AddModelUseMaterial(RPGrpShadowSrc* pModel, f32 density);
    void Unk_80257BC8(const RPGrpModel* pModel, bool flag);
    bool Unk_80257C0C(RPGrpModel* pModel);
};

//! @}

#endif
