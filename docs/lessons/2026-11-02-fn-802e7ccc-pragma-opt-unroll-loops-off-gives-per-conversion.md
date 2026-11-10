# fn_802E7CCC: #pragma opt_unroll_loops off gives per-conversion 0x4330 hi-word stores (76.9 -> 92.0)

- status: works
- tags: unroll,int-to-float,0x4330,opt_unroll_loops,RPBox_802e7b94,fnmsubs
- scope: Pack/RPSports
- source: claude opus worker 2026-11-02

symptom: fn_802E7CCC 76.9%, 568 vs 560 B: hi-word stored once at entry instead of at each of 4 int-to-float conversions; fnmsubs vs fsubs
cause: IRO fully unrolled the 2-trip loop (body 65-67 IR nodes, default opt_unroll_instr_count limit ~100), so the conversion count was taken post-unroll. +20 nodes cannot exceed the limit. With IRO unrolling off the backend still unrolls and stores a hi word per conversion
fix: #pragma opt_unroll_loops off/reset around the fn (file-wide also no regressions); f32 t = 0.1f*dt as a named local (inline arg copy fuses to fnmsubs); loop body order sumA+=, sumB+=, prod*=; local w = Box3Lerp(r,0.5f,1.0f) and sp = f1B4*f94 fix commutative fmuls operand order; manual f1C0*(1-t)+prod*t 92.0. Remaining: FPR colouring prod f1 vs f8, sumA f9 vs f10 (pre-RA schedule puts lfs 0x1c0 before prod*t); regsearch 8 min no gain. IR node costs: x = x + y vs += +3/stmt; repeated self->elem[i].plr vs p local +13; f32 sign getter +5/call; value-returning helper +18/call
