# ScreenEffectBase captureEfb: unit flag sweep and 4 more setBuffer store spellings, no gain

- status: fails
- tags: eggScreenEffectBase,captureEfb,flags,setBuffer,gfxe
- scope: egg/gfxe/eggScreenEffectBase
- source: session 2026-10-28

symptom: target stores via fresh 'addi r3,r30,0; stwx pTex,r3,r28' at the 3 setBuffer sites while its getBuffer loads reuse r31=addi r30,0; ours reuses r31 for the stores (1336 vs 1348 bytes, 98.1)
cause: setBuffer-store address node is not CSE'd with the getBuffer node in the original; no source form or flag found that splits them
fix: flag sweep on the unit (extra_cflags): -inline deferred/noauto/off, -O4,s, -sdata 0 -sdata2 0, -str reuse,readonly, -ipa file: nothing beats current (captureEfb stays 98.1; -ipa file only changes .sdata2 naming). Direct spBufferSet[type].mpTexBuffer= at the call sites 89.6; header setBuffer as ptr arithmetic / u8 offset 97.0 (+ regresses releaseEfb/popWorkBuffer); EffectBuffer* base local and TextureBuffer** pp identical 98.1. Untried: permuter, regsearch --generic, a TextureBuffer-side member for the store
