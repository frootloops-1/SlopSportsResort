# RPBsb_80252e7c fn_8025404C template-vtable name wall closed with R17 hand vptr stores

- status: works
- tags: template-vtable,hidden-vptr,TRPSndAudioHandles,8025404C,RPBsb_80252e7c,flip
- scope: Pack/RPSports/RPBsbScene/RPBsb_80252e7c

symptom: fn_8025404C 99.9: 8 lines reloc __vt__21TRPSndAudioHandles<8> / __vt__15BsbBallSndActor vs retail lbl_803C3FF8 / lbl_803C52B0
cause: compiler-emitted vptr stores name the real mangled vtables; symbols.txt keeps lbl_ names
fix: Same as fn_802597F4: *(void**)this = lbl_803C3FF8 first in local TRPSndAudioHandles<8> ctor; *(void**)this = lbl_803C52B0 and +0x3c = lbl_803C52B0+9 in BsbBallSndActor ctor (compiler stores dead, li r0,8 colouring kept). No symbols.txt edit. 55/55, flipped, DOL 0
