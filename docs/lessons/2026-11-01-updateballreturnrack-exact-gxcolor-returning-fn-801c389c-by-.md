# UpdateBallReturnRack exact: GXColor-returning fn_801C389C, by-value fn_801C37EC, emission order

- status: works
- tags: GXColor,declaration,emission-order,UpdateBallReturnRack,RPBow
- scope: Pack/RPSports/RPBowScene/RPBowBallReturnRack
- source: step2 2026-11-01

symptom: 98.3%: byte-store block (srwi/stb/extrwi reusing r0) and 246 DOL bytes at the flip gate
cause: u32 + bit-extract lets the pre-RA scheduler hoist the extrwi; real return type is GXColor; fn_8034DC98 was emitted before InitBallReturnRack in this reverse-source-order unit (objdiff blind to order)
fix: GXColor fn_801C389C(...) and void fn_801C37EC(..., GXColor) in the extern C block; GXColor c = f(); c.a = 255; reorder_fn.py (moves only // comments: move /** */ doc blocks by hand). Extra header static-inline locals in the .o are harmless (mwld strips them)
