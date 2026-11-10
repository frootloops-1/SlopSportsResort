# fn_8025EBE8 C body: post-states-loop load scheduling wall (96.5)

- status: fails
- tags: scheduling,unrolled-loop,RPBsb_8025a3e8,fn_8025EBE8
- scope: Pack/RPSports/RPBsbScene/RPBsb_8025a3e8

symptom: after correct split, C EBE8 14 diffs: lfs 0.0 (804C3430) hoisted into unrolled states reset loop; retail issues lfs/lis 59CC/59C0/lfs 34A0/li 0x78 right after the loop (looks like a block boundary)
cause: retail is probably a real C++ ctor with compiler-generated member-array construction; not reproduced
fix: failed: pointer loop, 8 explicit resets, self->states[i] loop, do-while countdown, 0.0f literal, f32 zero local, placement new BsbPlStateC[8] (emits a real loop). Asm kept (ledger 392)
