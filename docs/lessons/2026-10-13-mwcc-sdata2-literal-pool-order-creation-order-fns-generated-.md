# MWCC .sdata2 literal pool order = creation order; fns generated in reverse definition order

- status: open
- tags: mwcc,sdata2,literal,order
- source: RPGol_802b90b4

symptom: s32/u32 int->float magic doubles swapped vs target in RPGol_802b90b4
cause: target order needs 9F90(s32),98E8(0.9),9688(u32) generated before BA7D4, inconsistent with descending definition order
fix: dead ends: operand order, static inline helper at top, static helper at end (extra .text), inline 9688+dont_inline caller (fixes slot, but fn becomes weak). Untested: callee-before-caller generation via call graph
