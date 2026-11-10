# Strong fn emitted between weak helpers and a static inline (GXEnd) = define it inline before its first caller

- status: works
- tags: emission-order,inline,weak,ef,stripe
- scope: nw4r/ef/drawstrategy/ef_drawstripestrategy

symptom: ef_drawstripestrategy 100% in objdiff but order: ours DrawStripe,GetNum,GetTexmap,GXEnd,DrawParticle vs target DrawStripe,GetNum,GetTexmap,DrawParticle,GXEnd
cause: Weak/static-inline out-of-line copies are queued in order of first call in the caller; a strong function defined later in source is emitted in source order, but a function defined 'inline' before the caller is queued like a weak inline at its first call (here between GetStripeTexmapType and GXEnd). Moving it before the caller without 'inline' just makes it first in text.
fix: Move CalcAxisMtx/CalcRotMtx/DrawParticle before the dont_inline pragma region + DrawStripe and mark DrawParticle 'inline'. Codegen unchanged, order check clean, DOL 0 bytes, unit flipped to Matching.
