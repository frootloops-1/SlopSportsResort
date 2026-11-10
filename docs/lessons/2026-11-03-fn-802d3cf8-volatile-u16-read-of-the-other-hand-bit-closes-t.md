# fn_802D3CF8: volatile u16 read of the other-hand bit closes the last subf/colour pair (12 -> 0)

- status: works
- tags: fn_802D3CF8,RPBox_802cf93c,volatile,subf,colour-order,regalloc
- scope: mwcc GC/3.0a5.2, Pack/RPBox
- source: docs/marker-ledger.md row 141

symptom: call arg self->w148 == ((h1E>>6&1)^1): target has w148 in r0 and the lhz/extrwi/xori chain in r5 with subf r0,r0,r5; ours had them swapped, and chain-first spellings (BoxEq(chain,w148), chain==w148, comma forms) fixed the colours but flipped the subf to subf r0,r5,r0
cause: subf rA is the left operand of ==; colouring is descending vreg number. Plain spellings tie emission order to operand order so one of the two always loses
fix: int hand = ((*(volatile u16*)&o8->h1E) >> 6 & 1) ^ 1; then self->w148 == hand (w148 left). Volatile read is eager so the chain vregs are lower than the w148 load, w148 coloured first. Also drop the f14 local (pass in.f14 inline), keep f108 local. Single-use plain locals are forward-substituted and do not work; BoxEq(chain, w148) helper gets colours right with subf flipped (2 lines)
