#include <Pack/RPGraphics.h>

#include <cstdio>


/**
 * @brief Replaces a texture on the specified model
 *
 * @param pModel Target model
 * @param pName Texture name (format string)
 * @param ... Format string arguments
 */
void RPGrpShadowTexture::Replace(RPGrpModel* pModel, const char* pName, ...) {
    char buffer[255];

    std::va_list list;
    va_start(list, pName);

    // @bug Unsafe string operations
#if defined(BUG_FIX)
    std::vsnprintf(buffer, sizeof(buffer), pName, list);
#else
    std::vsprintf(buffer, pName, list);
#endif

    EGG::ShadowTexture::Replace(pModel->GetModelEx(), buffer);

    va_end(list);
}

/**
 * @brief Adds a new model to the shadow texture
 */
void RPGrpShadowTexture::AddModel(RPGrpModel* pModel, f32 density) {
    AddModelEx(pModel->GetModelEx(), density);
}

void RPGrpShadowTexture::AddModelUseMaterial(RPGrpModel* pModel, f32 density) {
    AddModelEx(pModel->GetModelEx(), density);
    m_mdlList[m_mdlNum - 1].useMat = true;
}

bool RPGrpShadowTexture::Unk_80257C0C(RPGrpModel* pModel) {
    return Unk_801B51FC(pModel->GetModelEx());
}

void RPGrpShadowTexture::Unk_80257BC8(const RPGrpModel* pModel, bool flag) {
    ModelBind& bind = m_mdlList[Unk_801B54FC(pModel->GetModelEx())];
    bind.mUnk9 = flag;
}

void RPGrpShadowTexture::AddModel(RPGrpShadowSrc* pModel, f32 density) {
    AddModelEx(pModel->mpModelEx, density);
}

void RPGrpShadowTexture::AddModelUseMaterial(RPGrpShadowSrc* pModel,
                                             f32 density) {
    AddModelEx(pModel->mpModelEx, density);
    m_mdlList[m_mdlNum - 1].useMat = true;
}
