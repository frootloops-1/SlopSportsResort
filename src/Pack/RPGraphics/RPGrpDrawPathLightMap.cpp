#include <Pack/RPGraphics.h>

#include <egg/gfxe.h>

/**
 * @brief Constructor
 *
 * @param pRenderer Scene renderer
 */
RPGrpDrawPathLightMap::RPGrpDrawPathLightMap(EGG::ScnRenderer* pRenderer)
    : RPGrpDrawPath(pRenderer) {

    mpLightTextureManager = pRenderer->getLightManager()->GetLightTextureManager();
}

/**
 * @brief Replaces the textures of a model with the light map texture
 *
 * @param index Light texture index
 * @param pModel Model
 */
void RPGrpDrawPathLightMap::ReplaceModelTexture(u16 index,
                                                RPGrpModel* pModel) {
    if (pModel->GetKind() != RPGrpModel::Kind_RFL) {
        mpLightTextureManager->replaceModelTexture(index,
                                                   pModel->GetModelEx());
    } else {
        RPGrpTexture texture(mpLightTextureManager->getTexture(index));
        pModel->ReplaceTexture(mpLightTextureManager->getTexture(index)->getName(),
                               texture, true);
    }
}
