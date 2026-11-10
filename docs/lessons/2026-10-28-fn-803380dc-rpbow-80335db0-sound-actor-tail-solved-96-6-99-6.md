# fn_803380DC (RPBow_80335DB0) sound-actor tail solved 96.6 -> 99.6 with BowPinSndActor : TRPSndAudioActorBaseWithHandles<4,4>

- status: works
- tags: RPBow_80335DB0,fn_803380DC,sound-actor,class-model,TRPSndAudioHandles,li-r0
- scope: RPBow_80335DB0
- source: claude/flip-bow-1028 sonnet

symptom: li r4,8 with addi r0,r3,0x24 hoisted above stw 0x44 (retail li r0,8 and addi after)
cause: inlined actor ctor must go through TRPSndAudioActorBaseWithHandles<N1,N2>; only N1+N2=8 is known
fix: Bsb-template class block: explicit specialisations of TRPSndAudioHandles<8> and TRPSndAudioActorBaseWithHandles<4,4> with out-of-line virtuals/dtors, hand-built u8[8][4] handle array + __construct_array, BowPinSndActor ctor(1) + u32 unk68 (size 0x6C, name and split inferred), plain new (no placement-new, no R17 marker needed). Unit .data stays STRAY-only. Remaining diff = 4 reloc names: lbl_803CA588 -> __vt__14BowPinSndActor, lbl_803C3FF8 -> __vt__21TRPSndAudioHandles<8> (both shared by ~7 Bow units and 17 src files; renames need all users updated)
