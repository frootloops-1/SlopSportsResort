# ef_animcurve Texture: r31 node is n=length-1 from CalcCurveFrame, pHeader==pCmdList aliasing canonicalised

- status: fails
- tags: ef_animcurve,texture,callee-saved
- scope: nw4r/ef/ef_animcurve
- source: worker a98dbf84, 2026-10-27

symptom: Texture 99.4%: pCmdList copy should get r31 (orig), ours gives r31 to n and pCmdList last (r24)
cause: r31 node is n=length-1 in CalcCurveFrame TURN+fitting branch (tick only shares it); extra inline wrapper fixes seed>tick>pParticle order but pCmdList stays last (99.1)
fix: dead: pHeader==pCmdList alias (cast at call, key table from pCmdList+sizeof, kindType/randomSeed via pCmdList, in-place advance, const header ptr, u8* const params) identical output; search helper u16 count/lo-hi order 99.2; forecast CalcFrameStep w/o rEnd 98.1 (u16)/97.0 (s32); move CalcCurveFrame, decl position, drop/u32-type n identical. Note CalcCurveFrame and ...Child share n/count text: global replaces hit Child (97.9->97.5)
