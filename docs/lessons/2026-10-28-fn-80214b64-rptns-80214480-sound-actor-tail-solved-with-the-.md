# fn_80214B64 (RPTns_80214480) sound-actor tail solved with the golf class model: TnsSndActor : TRPSndAudioActorBaseWithHandles<3,3> (98.3 -> 100, unit flips; bytes-matched with one R17 marker)

- status: works
- tags: RPTns_80214480,fn_80214B64,sound-actor,TRPSndAudioHandles,class-model,li-r0,R17
- scope: Pack/RPSports/RPTnsScene/RPTns_80214480
- source: orchestrator-1028

symptom: after bl __construct_array retail li r0,6 / stw r0,0x40 / stw r0,0x44 / addi r0,r3,0x24; ours li r4,6 with addi r0 above stw 0x44. 6 = N1+N2; object 0x64 = 0x60 + u32 unk60
cause: same as fn_802B54A0: the inlined actor ctor must go through the intermediate TRPSndAudioActorBaseWithHandles<N1,N2>; only the total N1+N2 is known (the <3,3> split and name TnsSndActor are inferred)
fix: Copy the RPSndObject.h classes locally (Disposer / RPSndAudioActorBase / TRPSndAudioHandles<N> / TRPSndAudioActorBaseWithHandles<3,3>) + TnsSndActor ctor(1) with out-of-line virtual dtor; body state->field3C = new TnsSndActor(). Hand vtable arrays named __vt__19RPSndAudioActorBase / __vt__11TnsSndActor sit next to the class (symbols.txt lbl_803C37B0 -> __vt__11TnsSndActor). The handles vtable is mangled __vt__21TRPSndAudioHandles<6> (21, not 22), cannot be named in C, and a hand derived vtable cannot point at a compiler getOuterPitch (casting a member-function pointer to void* is error 10247). Kept DOL 0 with a polymorphic Handles whose ctor writes *(void**)this = lbl_803C3818 then calls __construct_array itself (the compiler's own vptr store is then dead and dropped): MATCH-PENDING (R17) + ledger row 28. Unused weak WithHandles/Handles vtables, dtors, get3DPosition, getOuter* and their 1.0f pool entry are dropped at link. Failed: non-polymorphic Handles with a manual secondary vptr (97.7/97.8: user array not CSE'd with the compiler's vtable, so primary and +0x24 get separate lis/addi). Branch claude/actor1-1028 (e7ea24604 + b13f03ecb flip).
