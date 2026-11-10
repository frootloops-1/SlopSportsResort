# RPUtl_801C67B8 struct-init then scale and non-CSE sum close fn_801C67B8 90.6 -> 99.9

- status: works
- tags: mwcc,cse,hermite,decl-order
- scope: Pack/RPUtility/RPUtl_801C67B8
- source: claude/rputl-c67b8-1027

symptom: missing frsp after fneg, extra callee-saved GPR, b.x reused CSE'd extra+len, axis/start regs swapped
cause: retail inits Pair {1, diff} then tangent.y *= scale; tangentB = {1, -tangentA.y}; b.x written so extra+len is not a CSE of the scale sum; start declared before the axis loop
fix: Pair tA = {1, d}; Pair tB = {1, -tA.y}; tA.y *= ...; b.x = (f32)((end - start) + 1 + extra); 's32 start;' before 'for (s32 axis...)' (6B64: 's32 start, axis;' 136 -> 96 lines)
