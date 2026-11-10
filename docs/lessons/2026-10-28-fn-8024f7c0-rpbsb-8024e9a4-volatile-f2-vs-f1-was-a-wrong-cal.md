# fn_8024F7C0 (RPBsb_8024e9a4): volatile f2-vs-f1 was a wrong callee prototype, not colouring

- status: works
- tags: regalloc,fpr,prototype
- scope: RPBsb_8024e9a4 fn_8024F7C0
- source: FPR experiment 2026-10-28, branch claude/fprB-1028

symptom: fadds result f2 vs f1, 8 earlier source variants and a permuter run no gain
cause: fn_80271564 was declared (BsbScn6*) but takes (self, f32 dt) and the original passes the dt local already in f1, which keeps dt live across the switch and blocks f1
fix: correct prototype to (BsbScn6*, f32), calls fn_80271564(self, dt), drop (void)dt and cast-through-pointer workarounds. General check: when a volatile value avoids a register that looks free, look for an unused FP/int arg on a callee on the same path (other units may already declare the right prototype)
