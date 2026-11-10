# fn_80281A88 (RPBsb_802817a0) second Opus pass: forwarding is offset-0 only; operator= near miss 96.4

- status: fails
- tags: rpbsb,frsp,forwarding,copymtx,operator=,parked
- source: claude/bsb-1a88-1103f worker report

symptom: 97.3%: frsp f0,f11 on the first copyMtx load of m2[0][0]; retail reloads lfs f5,0xa8 and uses 6 distinct FPRs (f0,f9,f6,f5,f8,f7)
cause: Pre-RA optimizer treats lfs 0(r38) (r38=addi r1,m2) as the same address as stfs r1,m2+0, so only the offset-0 load of the first unrolled iteration is forwarded; an aliasing store between kills it (tested with a throwaway self->f270=0) but retail has none
fix: Parked after 2 Opus tries. Near miss: BsbMtx::operator= with the 3x4 nested copy loop (as in RPBsb_80258768) + m2 = m + overwrite cols 2/3 removes the frsp, but the late-unrolled loop reuses 2 regs per iteration (96.4). Dead: f32* store, single i<3 loop, nested loops 96.4-96.5, m2=m struct copy 85.2, copyMtx body variants (row ptr, flat 12, ptr+=4, u32 idx, named temp) identical, manual inner unroll 75.2, do-while 76.9, pragmas peephole off 92.1, opt_strength_reduction off 64.3, opt_unroll_loops off 72.6, optimization_level 2 60.5, opt_loop_invariants/dead_assignments off no change. Next if retried: tools/mwcc_sched_trace.py on the operator= variant to see where the 2-register reuse comes from
