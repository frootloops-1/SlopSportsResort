# RPUtlDirMath fn_801BD7E0 Hermite: weights match, callee-saved f29-f31 weight colouring not reproduced (~25 forms)

- status: fails
- tags: RPUtlDirMath,fpr,hermite,scheduling
- scope: Pack/RPUtility/RPUtlDirMath
- source: claude/dirmath-1027

symptom: target keeps start/startTangent/endTangent in f31/f30/f29 and computes end late; frame 0x40 with no locals. Ours keeps all volatile (no FPR saves) or reserves 0x30 of stack
cause: unknown; pre-RA pressure in retail exceeds 14 FPRs, but forms that load all 12 values early (register f32 locals) still stay volatile; POD struct locals (V3 a={..}) give callee-saved but reserve stack
fix: failed: direct pointer reads, scalar locals first/after, stage-wise statements, hermComp inline, nw4r VEC3/HermV class temps (huge), weight statement permutations (24+), weights via out-param inline, non-const params (30%), register locals. Works: pool order via 'three' local before twice; math_arithmetic.h guard + dropping eggVector.h include removes stray OSFastCast .text; source in descending order for emission
