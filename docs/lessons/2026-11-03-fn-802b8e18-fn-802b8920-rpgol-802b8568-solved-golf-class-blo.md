# fn_802B8E18/fn_802B8920 (RPGol_802b8568) solved: golf class block + golRemapClamp-style Remap2

- status: works
- tags: rpgol,sound-actor,remap,fpr
- scope: src/Pack/RPSports/RPGolScene/RPGol_802b8568.cpp

symptom: fn_802B8E18 97.2 li r0/r4 sound-actor tail; fn_802B8920 99.9 f0/f1 swap of in0 vs zero literal
cause: hand-written inline ctor vs real class model; Remap2 in1-=in0 form allocates zero literal below in0
fix: copy the RPGol_802b4f2c class block (Disposer/RPSndAudioActorBase/TRPSndAudioHandles<N> with R17 hand vptr/WithHandles<5,5>/GolSndActor) and use plain new GolSndActor(); Remap2 as float d=in1; float r; if (0.0f==(d-=in0)) r=out0; else r=out0+(out1-out0)*(v-in0)/d; return r (as golRemapClamp in RPGol_802c441c). Unit then 36/36 syms, FLIP-OK
