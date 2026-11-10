# DrawPathDOF Standard closed: GXSetFog prototype had the wrong parameter order (SDK is type,startz,endz,nearz,farz,color)

- status: works
- tags: drawpathdof,call-args,prototype,gx,scheduler
- scope: egg/gfxe/eggDrawPathDOF
- source: worker q-dofstd-1029

symptom: internalDrawStandard 4 lines: far(0x1c) lfs before fnmsubs and near(0x18) after it, both after the fog colour stb copy; no source spelling of the call reached it
cause: include/revolution/GX/GXPixel.h declared GXSetFog(type, color, start, end, near, far); the RVL SDK man page (RVL_SDK/man/en_US/gx/PixelProc/GXSetFog.html) has GXSetFog(type, startz, endz, nearz, farz, color). Same ABI (color pointer still r4, floats f1-f4), but MWCC builds the by-value struct copy and the inline-getter pre-evaluation in argument-list order, so with color LAST the copy comes first and getters land after it far-then-near
fix: SDK-order prototype + plain rScreen.GetNearZ()/GetFarZ() args: Standard exact, unit 10/10, marker removed; all 11 other GXSetFog caller units (GXPixel, GXInit, RFL_MakeTex, ut_CharWriter, g3d_fog, g3d_state, ef_drawstrategyimpl, eggFog, eggPostEffectBase, eggShadowTextureManager, eggStateGX) stay exact, flipped link DOL 0. General: when an arg-order wall resists every spelling, check the callee prototype against the SDK man pages / forecast headers before steering
