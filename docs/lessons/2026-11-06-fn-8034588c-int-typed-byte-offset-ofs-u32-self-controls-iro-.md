# fn_8034588C: int-typed byte offset ofs + (u32)self controls IRO CSE operand order (99.0 -> 100)

- status: works
- tags: cse,iv,operand-order,inline-accessor,RPBow_803433E4
- scope: Pack/RPSports/RPBowScene/RPBow_803433E4

symptom: retail add IV,self (r0) shared by -= and struct-copy read, then add mulli,(IV+self); direct pin[n] gives right shape but VN vreg colours late; pointer-typed self+n*0x30 holder gives r0 but self,IV order and a second IV
cause: explicit self+n*0x30 becomes an IRO CSE @temp (r0 colour); pointer+int is canonicalised pointer-first, int+int keeps written order; the outer operand order follows the written lane*size + (inner) sum; n*sizeof (unsigned) and n*0x30 (signed) are distinct IVs
fix: accessor: int ofs = n * 0x30; return ((Mgr*)(lane * sizeof(Row) + (ofs + (u32)self)))->lay[0].pin[0]; for the -= and m read, stmt1 as *(T*)((u8*)lay[lane].pin + n * 0x30): harness 9 -> 0 (R17 256). Dead: pointer-typed sums in any order (3), n*0x30 + (u32)self without the ofs local (3), stmt1 pin[n] direct (25-63), n*sizeof anywhere (25-43)
