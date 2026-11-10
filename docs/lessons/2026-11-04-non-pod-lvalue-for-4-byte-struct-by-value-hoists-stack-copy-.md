# Non-POD lvalue for 4-byte struct by value hoists stack-copy addi

- status: works
- tags: gxcolor,by-value,non-pod,stack
- scope: global
- source: docs/llm_matching_tricks.md 3.5

symptom: addi rX,r1,imm recomputed per call vs hoisted before loop; colour arg evaluation order
cause: MWCC hoists the hidden-pointer stack copy address only for non-POD class lvalues
fix: static inline const nw4r::ut::Color& AsColor(const GXColor* c) { return *static_cast<const nw4r::ut::Color*>(c); } and pass AsColor(p)
