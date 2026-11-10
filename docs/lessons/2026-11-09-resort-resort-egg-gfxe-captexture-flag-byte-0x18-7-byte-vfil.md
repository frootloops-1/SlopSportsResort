# resort: Resort EGG gfxe: CapTexture flag byte 0x18 + 7-byte VFilter, PostEffectBase vptr 0x28, BLEND_MUL=7

- status: works
- tags: resort,EGG,PostEffect,CapTexture,layout
- scope: resort
- source: RP batch 5 (2026-11-09)

symptom: RPGrpView ScreenEffect::Draw stuck at 52% with ogws EGG
cause: newer EGG: CapTexture flags at 0x18, clear colour 0x19, 7-byte vfilter aggregate; PostEffectBase fields first, vptr 0x28, vtable dtor/draw/setMaterialInternal/loadTextureInternal/drawScreenInternal; TextureBuffer::alloc out of line; DrawGX blend table has an extra entry
fix: headers in include/egg/gfxe carry the Resort layouts with addresses; ScreenEffect::Draw 100 (two identical blur paths under a u16 .sdata flag)
