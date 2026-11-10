# Audio actor ctor li 10 in r0 vs r4 (97.2; also fn_802B54A0)

- status: open
- tags: ctor,regalloc
- scope: RPGol_802b8568
- source: fn_802B8E18

symptom: li r4,10 and second store after addi r0,vt+0x24
cause: unknown; real class TRPSndAudioActorBaseWithHandles/TRPSndAudioHandles<10>
fix: dead ends: chained assign, local n, no vt temp, early vt, typed struct, inline stores, +0x3c sub-struct ctor; next: real class view from include/Pack/RPAudio/RPSndObject.h
