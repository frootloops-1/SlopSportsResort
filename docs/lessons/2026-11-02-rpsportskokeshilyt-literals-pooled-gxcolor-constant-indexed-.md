# RPSportsKokeshiLyt: literals, pooled GXColor constant, indexed members for loop IV order, VEC3 ctor for stack slots

- status: works
- tags: literals,loop-iv,vec3,gxcolor,RPSportsKokeshiLyt
- scope: RPSportsKokeshiLyt

symptom: .rodata 6, .data 0, .sdata2 67; fn_801CF808 97.5, fn_801CEFCC 99.4
cause: string blob extern; three 1-byte sdata2 symbols are one pooled GXColor FFFFFF00; explicit pointer increments lag SR IVs
fix: literals + local effects[4]; GXColor color={255,255,255,alpha} (merge sdata2 symbols to one size-4); KokeshiPlayer* player=&self->players[i], icons[i]; nw4r::math::VEC3 pos(m03,m13,m23); row=base+i*0x38 at first use; hand vtable (R17 116). Remaining GPR colouring: F808 text/shadow r27/r26 before IVs; EFCC frame r29/count r28.
