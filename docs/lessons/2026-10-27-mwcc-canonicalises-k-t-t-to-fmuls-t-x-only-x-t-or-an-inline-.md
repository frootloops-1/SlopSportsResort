# MWCC canonicalises (k*t)*t to fmuls t,X; only x *= t or an inline param temp keeps X first

- status: fails
- tags: mwcc,fpr,operand-order,hermite
- scope: Pack/RPUtility/RPUtl_801C67B8
- source: claude/rputl-c67b8-1027

symptom: target fmuls f23,f23,f6 (X first) for 2t*t; every expression spelling gives fmuls f23,f6,f23
cause: commutative operands reordered (leaf t first) unless the left is a variable; *= locals / mul() helper / scaledSquare get the order but push hoisted 2.0/3.0 into callee-saved FPRs (frame 0x110 -> 0x100)
fix: failed: 54 hermite forms (e/v/mul per product x t*t local), by-value Pair, const f32& t, t as expression arg; residue parked at 6 lines
