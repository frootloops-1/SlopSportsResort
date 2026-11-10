# Compound-literal stack temp slots 1st,4th,3rd,2nd order = fully unrolled loop

- status: works
- tags: egg,PostEffectBlur,unroll,stack,loop,inline
- scope: egg/gfxe/eggPostEffectBlur
- source: claude

symptom: 4 inlined resets with GXColor compound literal: stack temps at 0x14,0x08,0x0C,0x10 (ours 0x14,0x10,0x0C,0x08); refs/plain calls/index loops no change
cause: MWCC full unroll appends loop-body temp copies after the original; index loop mBlurData[i] or u32 bound does not unroll
fix: BlurData* p = mBlurData; for (int i = 0; i < 4; i++, p++) p->reset(); (literal int bound; i < CIRCLE_MAX u32 does not unroll)
