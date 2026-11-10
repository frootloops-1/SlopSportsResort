# fn_80205D10: real literals at pool offsets, VEC2 slot order, sdata2 boundary moved

- status: works
- tags: literals,string-pool,VEC2,stack-slot,split-boundary,fn_80205D10,R17,RPSports
- scope: Pack/RPSports/RPSportsCommon/RPSports_80205c74
- source: wave3 2026-11-01

symptom: 84.6%: extern lbl_8038A308+off re-materialised per use; stack slot order; .sdata2 66.67
cause: real literals give an early pool-base register; a return value of nw4r::math::VEC2 (derived _VEC2 with ctors) does return temp + word copy-init with the passed local at the lower address; named consts always precede a TU's own codegen literals so the two floats after the @double belong to the NEXT unit
fix: literals via descending source order (reorder_fn), data tables with literals, dead N_scene_00 array (R17 row 71), #include nw4r/math/math_types.h + real VEC2, SpStartPointSe (R17 row 70); splits: 80205c74/8020634c .sdata2 boundary -> 0x804C21E8 with lbl_804C21E8=-5000.0f, lbl_804C21EC=0.5f defined at the end of RPSports_8020634c.cpp; lbl_8038A308 -> @stringBase0 size 0x148; lbl_804C21D8 size 8; gap_12_804C21DC_sdata2 deleted. Dead: static const char* const p used in code is not folded to the literal address
