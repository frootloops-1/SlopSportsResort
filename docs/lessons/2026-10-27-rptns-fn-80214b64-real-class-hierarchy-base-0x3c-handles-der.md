# RPTns fn_80214B64: real class hierarchy (base 0x3C + handles + derived with unk60) with inline ctors and new gives same 6 diff lines

- status: fails
- tags: rptns,fn_80214B64,class,ctor,scheduler

symptom: li r4,6 and addi r0,r3,0x24 hoisted above stw 0x44 persists
cause: actor is TRPSndAudioActorBaseWithHandles-like: handles vptr/counts at 0x3C/0x40/0x44, 6 SoundHandles at 0x48, derived adds a 4-byte member at 0x60 (alloc 0x64). Modelling it as classes with nested inline ctors and operator new is byte-identical to the raw-offset version, so the wall is not the ctor shape
fix: Branch claude/rptns-class-1027 (not merged) holds the class version. Remaining ideas: IR-level reason r0 is busy (RA picks r4 so addr+0x24 is computed before the 6 range ends); try extern vtable decl instead of TU-local weak array, or real header TRPSndAudioActorBaseWithHandles<3,3>.
