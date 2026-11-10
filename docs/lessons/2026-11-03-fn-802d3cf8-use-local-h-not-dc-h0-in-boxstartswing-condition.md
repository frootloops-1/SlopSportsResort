# fn_802D3CF8: use local h (not dc->h0) in BoxStartSwing condition; 44 -> 35 lines

- status: open
- tags: regalloc,gpr,vreg-order,RPBox_802cf93c
- scope: Pack/RPSports/RPBoxScene/RPBox_802cf93c fn_802D3CF8

symptom: BoxStartSwing compare loaded dc->h0 twice; h r9 vs r10 and compare operand order off
cause: reloading dc->h0 creates an extra temp vreg that shifts colouring of neighbouring GPR temps
fix: write 'if (h != 0 && self->w148 == dc->w14)' using the already-loaded h. Operand swap (39), w14 local (39), w148 local (35, no gain) do not help. Remaining 35 lines: b r6 vs r3, in.flags r3 vs r4, lwz 0x148/0x14 order, later clrlwi r10 block.
