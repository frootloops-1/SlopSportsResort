# resort: EGG::LightManager layout differs from ogws (LightTextureManager* 0x14, flags u16 0x1E)

- status: works
- tags: resort,EGG,layout,LightManager
- source: rp-egg-layouts worker 2026-11-09

symptom: RPGrpDrawPathLightMap ctor 99.9%: reads LTM at +0x14, header +0x20
cause: Resort's EGG is newer
fix: layout from ctor fn_801AF5D0, DoneDraw 0x801AFCE0, fn_801AFD0C (see eggLightManager.h); AmbientObj stride 0xC and LightObject array stride 0xA4 noted, not yet modelled
