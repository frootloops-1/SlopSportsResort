# fn_80327F0C 95.3 -> 97.6: drop the fusion hack, sweep independent def order; remaining b.z product order

- status: open
- tags: fn_80327F0C,scheduler,fpr,RPBow,partial
- scope: Pack/RPSports/RPBowScene/RPBow_80327F0C
- source: step2 2026-11-01

symptom: 95.3%; after: 27 lines, bz*bz before by*bz, k*xz/zm swap near the out2z store, b.y f4 vs f13, k-dot f13 vs f30
cause: scheduler tie-break order: urgency, then successors made ready, then height, then program order; stores through out-pointers chain so source store order is fixed; the original probably has yz ahead of the zz diagonal in program order but interleaving diagonal stores scored worse (86.9-96.2)
fix: natural xz + ym with ym used by both stores; six off-diagonal defs after the diagonal stores in order yz,xm,xz,ym,xy,zm (ten other orders identical); lbl_803CA640 vtable written as data (.data 100); lbl_804C6090 size 8->4 (.sdata2 100). Dead: separate m var (86%), dots before inverse (75%), diagonal values as locals with stores at end (<=94.1), commuting k*()/c*c, regsearch 8 min. Next: mwcc_dbg + color_sim to pin the vreg order that gives b.y=f13, k-dot=f30. Tooling: regsearch.py function_span fails on a two-line signature (use --src with a one-line copy)
