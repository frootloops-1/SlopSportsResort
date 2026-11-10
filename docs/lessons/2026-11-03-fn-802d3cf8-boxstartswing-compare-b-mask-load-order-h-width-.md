# fn_802D3CF8 BoxStartSwing compare/b/mask: load order, h width and local placement are all neutral (stays 35)

- status: fails
- tags: regalloc,gpr,vreg-order,forward-substitution,RPBox_802cf93c
- scope: Pack/RPSports/RPBoxScene/RPBox_802cf93c fn_802D3CF8

symptom: target loads dc->w14 before self->w148 (cmpw w148,w14), keeps b in r3 / in.flags r4, and keeps a 'clrlwi r10,r10,16' on the u16 h arg; ours loads w148 first, b r6, flags r3, mask elided
cause: colour order is descending vreg: X(w148) and Y(w14) temps are numbered above named b, so they colour first and take r0/r3, pushing b to r6; target needs b coloured before Y and X created after Y. Single-use locals and inline params are forward-substituted so load order follows the compare's left operand. The optimizer elides the 16-bit mask for any h spelling.
fix: failed (all stay 35 or worse): swapped operands (39, cmp order flips), reversed-param inline BoxEqRev, inline with named locals y,x, nested if with local cur, kind via BoxSwingKind inline taking b, BoxStartSwing body hand-inlined, dc/h/w/k declared at function top, h as u32/s32/u16 (same) or s16 (lha, 44), (u16)h / h&0xFFFF / (u16)(int)h / h+0 at the call, u16* read, h&0xFFFF at init, (u16)dc->h0. Open: what makes the optimizer keep the mask, and a way to create Y before X with cmpw X,Y.
