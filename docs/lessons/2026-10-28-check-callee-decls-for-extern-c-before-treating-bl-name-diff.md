# Check callee decls for extern "C" before treating bl-name diffs as a wall (RPBowActiveBall RenderModelSet 97.3 -> 97.4)

- status: works
- tags: extern-c,bl-name,RPBowActiveBall,RenderModelSet,F6,wall
- scope: Pack/RPSports/RPBowScene/RPBowActiveBall
- source: orchestrator-1028

symptom: RenderModelSet__Q27Bowling15RPBowActiveBallFv at 97.3%: 2 diff lines were call names (bl fn_801C389C / fn_801C37EC mangled in ours, unmangled in the original)
cause: callees declared as C++ functions get mangled names; the original calls them unmangled (C-linkage helpers)
fix: extern "C" { ... } declarations of fn_801C389C and fn_801C37EC in RPBowActiveBall.cpp: 97.3 -> 97.4. Remaining 2 hunks are class-3: byte-extract chain reuses r0 serially in the original (ours hoists extrwi into r5/r4) and VEC3Transform arg addi order r4 before r3. Failed: all 24 orders of color.r/g/b/a, GX_BITGET vs shifts vs casts, brace-init GXColor, u8 locals, f32 alpha local, u32/s32 packedColor, sibling RPBowBallReturnRack temp+copy (95.2), fn_801C389C inlined (89.9), PSMTXMultVec/VEC3TransformCoord (identical), src/dst/threshold order (84.8). permute.py setup fails: definition of Bowling::RPBowActiveBall::RenderModelSet not found in the unit's own code.
