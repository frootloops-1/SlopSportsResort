# Store-order vs colouring wall: inline helper args evaluated before body stores

- status: works
- tags: register-wall,store-order,inline-helper,eggLightTexture,SetBinaryInner,R17
- scope: egg/gfxe/eggLightTexture
- source: claude/lt-1027

symptom: SetBinaryInner 99.8: need hi/type/lo store order but type loaded before hi and coloured r5 (mask r6); all inline/local forms swapped r0/r5 or r5/r7
cause: args of an inlined call are evaluated (and numbered) before the body; argument order sets colouring of the two loads
fix: static inline SetMaskType(p, int type, u32 mask){hi=mask&0xFFFF0000; setDrawType(type); lo=mask;} called with (d.drawType, d.lightMask): 100, DOL 0; (mask,type) order swaps r5/r6. MATCH-PENDING R17
