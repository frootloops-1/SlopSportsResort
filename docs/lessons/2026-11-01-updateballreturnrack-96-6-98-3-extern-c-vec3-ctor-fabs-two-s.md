# UpdateBallReturnRack 96.6 -> 98.3: extern C, VEC3 ctor, fabs two-step, GXColor temp; byte-store block wall

- status: open
- tags: GXColor,scheduler,fn_801C389C,RPBow,partial
- scope: Pack/RPSports/RPBowScene/RPBowBallReturnRack
- source: step2 2026-11-01

symptom: 96.6%, size 1000 vs 992, f28-f31 colours, cm2hw, relocs
cause: externs inside namespace Bowling mangled; hoisted float constants colour wrongly when their degree >= limit in the first simplify pass (VEC3(x,y,z) ctor makes scalar params low registers); fsubs/fabs temp; missing lwz/stw copy of small struct
fix: wrap fn_ externs in extern C; VEC3 reflPosFinal(m03,m13,m23); i++,pBall++,pModelPair++; f32 d=a-b; d=__fabs(d); GXColor temp built then GXColor color = temp; NW4R_G3D_PLATFORM_GPU_H guard; delete gap_12_804C6894_sdata2. Residue 14 lines: after bl fn_801C389C target does srwi/stb/extrwi/stb/extrwi/stb reusing r0, ours hoists all three extrwi above the stores; #pragma schedule once reproduces the block but drops the function to 75%; same wall in RPBowActiveBall::RenderModelSet. Next: inline helper returning GXColor by value, or volatile/pointer-aliased store target; dead: GX_BITGET vs shifts, u8 locals, reused temp, unrolled loop, store order, aggregate init (95.3), ut::Color ctor
