# RPBow_80320EFC fn_80323228: real class views for sound-object ctors

- status: works
- tags: RPBow_80320EFC,fn_80323228,BowPinSndActor,RPBowNpcSndObject,vtable,class-model

symptom: li r4,8 vs li r0,8 for handle-count stores; se pointer merged with ctor result (r23 vs r26)
cause: hand-written field-by-field ctor model; the compiler's own (dead-store-eliminated) intermediate vptr stores change colouring
fix: new BowPinSndActor / new Bowling::RPBowNpcSndObject(player) on local class views (virtuals out of line, RPSndAudioActorBase virtuals non-pure to avoid abstract error; TRPSndObject<4> and TRPSndAudio3DActor<4> views). Placement new on a sub-object adds a null check (bad). Hand dead vptr stores are DSE'd and do nothing. Hand vtable arrays in .data can stay.
