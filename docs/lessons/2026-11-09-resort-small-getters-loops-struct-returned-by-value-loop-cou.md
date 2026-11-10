# resort: small getters/loops: struct returned by value, loop counter order, signed compares, fp_contract

- status: works
- tags: resort,first-pass,idioms
- scope: resort
- source: can-fld

symptom: 12-byte lwz a/lwz b/stw b/stw a copy; loop regs swapped; xori/srawi compare; unwanted fmadds
cause: hidden r3 return struct with u32 members; declaration order sets regs; signedness; -fp_contract on
fix: return a {u32,u32,u32} struct by value; declare s32 i before s32 n and compute n before the loop; use s32 operands for x<K; put each product in its own local to avoid fmadds
