# fn_8032F2B8 (RPBow_8032ADD8): hand vptr store lbl_803C3FF8 gives 99.5 -> 99.6 only; object temp r26 vs r27 still open (4x Sound3DActor struct ctor moves temp to r27 but drags b to r27)

- status: open
- tags: RPBow_8032ADD8,fn_8032F2B8,sound-actor,regalloc,R17,BowNewSnd
- scope: RPBow_8032ADD8
- source: claude/bow8-1028 sonnet

symptom: 26 diff lines: first new BowPinSndActor temp r26 vs retail r27 (shares with player r27); retail b=a+0x10 shares r26 with loop counter i
cause: first temp and b always land in the same register in every variant; need interference between them
fix: Recipe for the reloc names (not committed, would add an R17 marker for +0.1): *(void**)this = lbl_803C3FF8; in the local TRPSndAudioHandles<8> ctor, same as RPBow_80335DB0 (state saved by the worker as p1.cpp). Lever that moves the first temp to r27: struct BowNpc3D{void* mActors[4]; BowNpc3D(void* player){loop}} called ((BowNpc3D*)a)->__ct(player), but b moves r26->r27 (same score). Failed: x34 before x30 (47.4), BowNewSnd() into local first, u8* b/s32 i decl swap (99.1), new (a) Struct(player) (95.9, null check), whole 0x90 block as struct new (98.7, self r30), b in BowNpcBase ctor, i outside loop, s3 split. Untried: real class for the whole second block (needs lbl_803C3FC0 hand store and the RPBowNpcSndObject vtable stores at 0x78/+8/+0x2C, several more R17 markers)
