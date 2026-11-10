# ShadowTexture Draw: capture-format expression / decl-order / alpha-type variants do not reach target colouring

- status: fails
- tags: register,callee-saved,draw,parked
- scope: egg/gfxe/eggShadowTexture
- source: shd-1027

symptom: Draw 98.4, DOL 37 bytes flipped: target alpha=r31,w=r30,h=r29,x=r29,simple=r27; ours h=r31,alpha=r29,x=r27,simple=r31; final capture temps format r4/flags r6 vs r5/r4
cause: interference-graph colouring order; not decl order (alpha-first identical), x/y decl order only swaps x/y
fix: tried: inline cCaptureFormat[!alpha][fmt!=I8] (97.5), formats ptr+inline index (97.5), precomputed int format (97.7), intensity-before-formats (identical), int x;int y (98.4 swapped), posX/posY inline in Screen ctor (98.2), u32 alpha without flags temp (identical). Parked.
