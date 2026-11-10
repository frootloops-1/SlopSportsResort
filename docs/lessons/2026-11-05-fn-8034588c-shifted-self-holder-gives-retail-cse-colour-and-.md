# fn_8034588C: shifted-self holder gives retail CSE colour and stmt3 grouping but a second n IV

- status: fails
- tags: holder,cse,iv,RPBow_803433E4
- scope: Pack/RPSports/RPBowScene/RPBow_803433E4

symptom: need self+n*0x30 as an optimizer temp shared by stmt2/stmt3 (retail r0, stmt3 m source mulli+(IV+self))
cause: holder sh.p=(BowKabeMgr*)((u8*)self+n*sizeof(BowPinMtx)) + accessor sh->lay[lane].pin[0] gives exactly that, but the optimizer makes a separate IV (li r25,0) instead of reusing stmt1's pin[n] IV r29: harness 26 (extra reg/instr)
fix: Dead (harness, base 9): signed n*0x30 / (int)sizeof*n / n*0x30+self (64), (BowPinMtx*)self+n (96), &self->lay[0].pin[n]-0x30 (65), stmt1 through the same holder (33-103), pin-base byte-offset accessor (98), lay-array holder for stmt2/3 (35), combined stmt2+3 inline returning ref (9, same diff), all direct stmt3 spellings incl. named xD0 local (19). Untested: a shape whose IV is shared by stmt1 and the holder
