# Vector temp stack-slot swap: VEC3 shape + by-value operator+= + caller local

- status: works
- tags: rpgol,802b1a0c,stack-slot,struct-copy
- scope: Pack/RPSports/RPGolScene/RPGol_802b1a0c

symptom: fc8 += n*w: retail operator* out at sp+0x14, copy at sp+0x8; ours swapped (fn_802B3FF4)
cause: inlined-function locals go below caller locals/temps; copy source must be caller local, target an inline by-value param
fix: GolVec3 : GolV3 with empty ctor; operator+=(GolVec3 rhs); GolVec3 nw = n * w; self->fc8 += nw;
