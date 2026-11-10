# fn_801C3574 FPR wall is a scheduler (pre-RA) tie, not RA order; source shape cannot reach it

- status: fails
- tags: fpr,register,schedule,wall,frustum,permuter
- scope: Pack/RPUtility/RPUtlLytBase/fn_801C3574
- source: claude-sonnet

symptom: 60-66 diff lines; retail swaps two pairs vs ours (lfs 0x14 before stw 0xa0; fmuls d*hr before lfd height) and every FPR number follows
cause: MWCC schedules BEFORE register allocation (#pragma scheduling off changes GPR+FPR colours). Float colours follow the schedule. Schedule class is latency-critical-path driven: 116/120 prologue variants (optional locals w/h/d/hr/prod/ratio in all topological orders, z first, u16 locals, x=ratio*y, hr*d, named temps, reversed dir stores) give the same class as ours; replacing the fdivs by fmuls flips to lfs14-first, retail sits between. Permuter unusable (C parser rejects static_cast to reference; cref() inline helper regresses 66 to 180; stand-in run only ~120 iterations/10min).
fix: none: statement/local/order levers exhausted; remaining lever must change the ratio->x consumer DAG (retail's fdivs chain has lower priority than ours). Park unless a new inline-boundary idea for w/h/ratio appears. Harness: scratchpad compile-by-copy 1.3s/variant with wibo, score vs retail fn lines.

2026-10-28 follow-up (float-prologue DAG, scratchpad v4.py/v5.py, 162-instr layout kept):
- All 328 dependency-legal orders of {ratio,y,x,z,dir0..3} statements (stores interleaved with the float math) give the same schedule [stw_a0 frsp lfs14 lfd_a0 fmuls1]; source order of the prologue is irrelevant, not just "mostly".
- The latency model drives the class: `#pragma scheduling` 750/gekko = ours; 7400 = [lfs14 stw_a0 frsp fmuls1 lfd_a0] (one swap from retail); 603 = [lfs14 fmuls1 frsp stw_a0 lfd_a0]; none equals retail [lfs14 frsp stw_a0 fmuls1 lfd_a0], and retail is -proc gekko like the other 25 matching functions, so a pragma is not the answer (and would be a fakematch).
- Conclusion: the retail DAG differs in a way no source reordering reaches (a different node set pre-scheduling, e.g. an extra/different consumer or a differently-typed conversion). Unit stays parked.
