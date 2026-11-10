# fn_8031A0E0: kept member address (addi rX,self,K + psq 0/8(rX)) needs a VEC3* declared after the preceding copy-ctor

- status: open
- tags: RPBow_80319C98,fn_8031A0E0,addi,cse,psq,holder
- scope: RPBow_80319C98

symptom: retail addi r6,r29,0x1f8 then psq_l 0(r6)/8(r6) for self->v1F8 in a VEC3 lerp; ours folds to 0x1f8(r29)
cause: MWCC folds base+K into the displacement unless the address comes from a pointer local defined after the EGG::Vector3f Q copy-ctor (block/EH boundary) and indexed [1]
fix: VEC3* h=&self->v1EC; declared right after Q, read h[0]/h[1] -> exact addi and retail j*16 GPRs; costs +1 insn until the v1BC ps_mr is fixed (net 97.5->97.3), so not committed. Flat: refs, ptr holders anywhere earlier, (&v1EC)[1], lerp helpers
