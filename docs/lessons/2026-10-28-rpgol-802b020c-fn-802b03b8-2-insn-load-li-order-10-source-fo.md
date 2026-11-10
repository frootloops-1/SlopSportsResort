# RPGol_802b020c fn_802B03B8: 2-insn load/li order, 10 source forms and generic regsearch no gain

- status: fails
- tags: fn_802B03B8,RPGol_802b020c,schedule,regsearch
- scope: Pack/RPSports/RPGolScene/RPGol_802b020c
- source: session 2026-10-28

symptom: unit otherwise 100% (rodata/data/sdata/sdata2); target order is lwz r3,4(r30); li r0,2; lwz r4,0x4c(r31); stb r0,2(r3), ours loads other->f4c first
cause: scheduler tie-break; regsearch has only 72 variants for it (few mutation sites), score 20 = baseline
fix: dead: o/src declaration order (99.2), o decl then store then src (99.2), direct self->f4/other->f4c (99.2), copy before store (94.0), u8* o, dst/src locals (99.0/99.8). Not tried: permuter, hand-written site alternatives
