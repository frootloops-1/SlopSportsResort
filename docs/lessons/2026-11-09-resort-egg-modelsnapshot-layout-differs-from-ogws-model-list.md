# resort: EGG::ModelSnapshot layout differs from ogws (model list at 0x58, 12-byte ModelBind)

- status: works
- tags: resort,EGG,layout,ModelSnapshot
- source: rp-shadowtexture worker 2026-11-09

symptom: RPGrpShadowTexture AddModel/Replace off by offsets
cause: Resort's EGG is newer
fix: ctor 0x801B4F7C, InitList 0x801B50B4, reset 0x801B5138 (see eggModelSnapshot.h); ShadowTexture::Replace has a 3rd bool (li r6,0); RPGrpShadowTexture has a second AddModel/AddModelUseMaterial overload pair
