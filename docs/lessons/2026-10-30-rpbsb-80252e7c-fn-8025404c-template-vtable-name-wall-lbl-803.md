# RPBsb_80252e7c fn_8025404C: template-vtable name wall (lbl_803C3FF8 / lbl_803C52B0), same root cause as RPBowNpcManager

- status: open
- tags: f1,symbols,hidden,rpbsb,vtable,template,link
- scope: RPBsb_80252e7c, RPBowNpcManager, RPTns_8021ba24; symbols.txt
- source: claude/f1-bsb80252e7c-1031 worker report 2026-10-31

symptom: fn_8025404C 99.9%, only 2 vtable reloc names differ (lbl_803C3FF8 vs __vt__21TRPSndAudioHandles<8>, lbl_803C52B0 vs __vt__15BsbBallSndActor); all data 100%, 111/112 syms exact; throwaway Matching flip fails link with undefined TRPSndAudioHandles<8>::__vt
cause: weak vtable arrays lbl_803C3FF8/lbl_803C3FC0 are hand-defined in RPTns_8021ba24.cpp and externed by ~16 Bow/Gol/Tns/Bsb units; <8> is not a valid C++ identifier, and a symbols.txt alias does not give the linker a global definition. Hand vptr stores with lbl_ names regress li r0,8 colouring to li r4,8 (see d6dd1eb5f)
fix: Not applied. Project-wide task: model TRPSndAudioHandles<8> and TRPSndAudioActorBaseWithHandles<4,4> with real vtable emission (key function) in the owning unit, rename lbl_803C3FF8/3FC0/52B0 in symbols.txt, convert the ~17 hand-extern users. lbl_803C52B0 alone is easy (3 users) but useless until the other is resolved. Same blocker as the RPBowNpcManager InitAudioActors lesson.
