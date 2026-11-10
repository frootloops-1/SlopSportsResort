# LightManager LoadScnLightInner: backend induction offset coloured first; IRO forms give pointer induction

- status: fails
- tags: regalloc,LightManager,induction,IRO,egg
- scope: egg/gfxe/eggLightManager

symptom: clear loop offset r3/pp r5/obj r4 vs retail r5/r4/r3
cause: offset is created by the backend optimizer (highest vreg, coloured first); retail needs a low IRO-created offset like loop 2's
fix: failed: pSet->lightId[i], ref().lightId[i], named byte offset, u32 i (all IRO pointer induction + guard), GetLightID w/o copy, if-assign/int/u16/zero-init|= idx, shared i across loops; open: what makes IRO pick offset form (loop 2 has a call+continue)
