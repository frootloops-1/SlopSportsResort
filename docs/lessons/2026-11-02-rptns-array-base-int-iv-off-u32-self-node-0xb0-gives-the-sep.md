# RPTns array-base int IV: off + (u32)self->node + 0xb0 gives the separate add temp

- status: works
- tags: rptns,iv,address,add-operand-order,vreg
- scope: Pack/RPSports/RPTnsScene/RPTns_80244198
- source: opus 2026-11-02

symptom: orig add r4,off,self; addi r19,r4,0x200 (temp distinct from node); ours folded add/addi onto one vreg, or with &node[4] base emitted add self,off
cause: base pointer must be the array decay self->node (a separate frontend node), with the int IV first and the residual element offset (4*0x2c) as the last constant
fix: TnsNode* n = (TnsNode*)(off + (u32)self->node + 0xb0) with int off = i*0x2c: fn_802449E8 exact, fn_80246254 anm loop exact. (u32)&self->node[4]+off, (u8*)self->node+off then +4, (TnsPosSel*)(off+self)->node+4 all give add self,off or the folded vreg
