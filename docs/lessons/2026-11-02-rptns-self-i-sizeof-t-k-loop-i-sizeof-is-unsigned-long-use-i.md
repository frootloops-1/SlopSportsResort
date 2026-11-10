# RPTns self+(i*sizeof(T)+k) loop: i*sizeof is unsigned long; use int local off=i*0x2c, off+(u32)self+k

- status: works
- tags: RPTns,fn_802449E8,fn_80246254,strength-reduction,sizeof,operand-order
- scope: Pack/RPSports/RPTnsScene/RPTns_80244198

symptom: add has self before the offset IV and the spill slots swap (fn_802449E8 18 lines, fn_80246254 r28/r29 string-base swap)
cause: sizeof(T) makes the multiply unsigned long and mwcc canonicalises add operands self,off; an int local off = i*0x2c then off + (u32)self + 0x200 emits add off,self like the target
fix: fn_802449E8 99.8->100.0 (4 lines left: orig add into volatile temp r4 then addi r19, ours same vreg), fn_80246254 99.2->99.5; also drop the local tbl copy of lbl_804A6000 in fn_802449E8 (it swaps 0x10/0x14 spill slots). Dead ends: &self->node[4+i] (pointer IV 93.5), TnsBtnView cast+member, u8*/char* temps, inline helper, decl-order perms, regsearch 10min
