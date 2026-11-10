# drawAndCaptureTexture 99.7->100: call sibling members by their symbols.txt names via extern C

- status: works
- tags: egg,LightTextureManager,symbol-name,extern-c,join-moved
- scope: egg/gfxe/eggLightTextureManager

symptom: 3 'wrong lines' + 4-byte size mismatch: orig calls fn_800920CC, draw__..Fi (no r4 set), capture__..FRC8_GXColorb with r4=bool and no li r5; ours emitted getDrawSetting/draw()/capture(color,false) with extra li r5,0
cause: symbols.txt names for LightTexture draw/capture/getDrawSetting do not match the real call signatures (draw(void), capture(bool)); the header-based calls resolve to different symbols/arity
fix: extern "C" decls with the exact symbol names (fn_800920CC, draw__Q23EGG12LightTextureFi(LightTexture*), capture__Q23EGG12LightTextureFRC8_GXColorb(LightTexture*, bool)) in the manager cpp; proper fix is renaming those symbols to draw Fv / capture Fb in symbols.txt + eggLightTexture unit
