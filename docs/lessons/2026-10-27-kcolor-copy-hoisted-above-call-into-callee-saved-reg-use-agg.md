# KColor copy hoisted above call into callee-saved reg: use aggregate init, not compound literal

- status: works
- tags: egg,PostEffectBlurSimple,GXColor,hoist
- scope: egg/gfxe/eggPostEffectBlurSimple
- source: claude

symptom: lwz r30,0xc(r1) before bl GXSetNumTevStages, stw after; target lwz r0 after the bl
cause: GXColor color = (GXColor){0,0,0,mAlpha} copies the literal temp into a register-promoted local
fix: GXColor color = {0, 0, 0, mAlpha}; (stw 0 + stb alpha into the local, by-value copy after the call)
