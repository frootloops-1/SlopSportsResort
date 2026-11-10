# Third-party ef_animcurve.cpp (3070 lines) compared: shares ancestry with ours, no new lever; rank gap is compiler-independent

- status: fails
- tags: ef_animcurve,Texture,Child,fork,compiler-sweep,regsearch
- source: xfer-1028 third-party file

symptom: Texture/Child pHeader colour-rank gap (rank 14) unexplained
cause: The file's Child opens with the same local-declaration block as ours (we already derived from it). Compiled in our build (AC_TARGET_TEXTURE1/2/IND = 14/15/16 shim): Texture rank 14 perm 3 (same gap, op 10 imm 7 worse), Child rank 62 vs ours 60 (imm 68 vs 22), U8/Rotate far worse, no F32 match (its F32 takes two f32*, F32Vec2/Vec3/N, U8Vec3 do not exist in the original: symbols.txt has exactly 6 fns). Compiler sweep with the finer metric: GC 3.0a3..3.0a5.2 identical (rank 14), all Wii builds also rank 14 with 41-58 opcode mismatches, pre-3.0 GC builds cannot parse project headers (OSFastCast.h)
fix: No source change. The rank-14 Texture gap is independent of compiler build, so it is source structure. Its CalcFrameStep(pCmdList,...)+bool end, SearchKeyStep, and u16 frame are alternative shapes already approximated in ours
