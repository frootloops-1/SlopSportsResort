# fn_802D3CF8: volatile w14 read + getter-returned b/h + f14/f108 locals take 35 -> 12 lines

- status: works
- tags: regalloc,gpr,volatile,inline-getter,vreg-order,scheduler,RPBox_802cf93c
- scope: Pack/RPSports/RPBoxScene/RPBox_802cf93c fn_802D3CF8

symptom: target loads dc->w14 before self->w148 (cmpw w148,w14), b in r3, mask clrlwi r10,r10,16 kept on the u16 h arg; ours loaded w148 first, b r6, mask elided
cause: tree emission is lazy: single-use locals and inline params are forward-substituted into the use site (left operand emitted first), so only an eager construct reorders loads. A volatile read is emitted at declaration. Inline getter returns keep the u16 argument mask and are @temps numbered above call-arg temps, so b colours first. Post-RA scheduling follows from the colours (lwz X2 hoists once its register is not shared with the lhz chain).
fix: volatile s32 cur read in an if(h!=0) block, int h = dc->GetHi(), BOOL b = BoxCanSwing(o5,self) inline getter, f32 f14/f108 locals before the call; u32 fl local not needed. Remaining 12 lines: arg-7 compare self->w148 == ((h1E>>6&1)^1) colours chain r0 / X2 r5 (target X2 r0, chain r5) with subf direction chain-X2. Chain-first emission (operand swap, named locals, struct, x2-isP) flips colours to the target's but also flips subf to X2-chain; every spelling that keeps subf(X2,chain) emits X2 first. Open.
