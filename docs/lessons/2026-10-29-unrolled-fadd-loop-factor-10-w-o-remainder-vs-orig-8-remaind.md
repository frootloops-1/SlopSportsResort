# Unrolled fadd loop: factor 10 w/o remainder vs orig 8 + remainder

- status: fails
- tags: rpbox,802c8360,unroll,sum-loop
- scope: RPBox_802c7924
- source: x-golbox-1029

symptom: BoxStat ctor 'for i<n sum+=arr[i]' n=80: ours unrolls by 10 (ctr 8, frsp+stfs each step), orig unrolls by 8 with ctr 9, a remainder loop to 0x50 and few stores
cause: unknown; tried local accumulator (worse 83.2), (s32)n bound (worse 78.9), literal 80 for nL, sum = sum + x (no change)
fix: none yet (SOLVED 2026-10-29, see 2026-10-29-unroll-x8-ctr-n-1-3-remainder-with-constant-n-count-was-opaq: the count was opaque at unroll time; signed int n + arithmetic count)
