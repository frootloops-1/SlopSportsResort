# fn_801FC7F8 limit r0: all variables numbered below codegen temps; 10 spellings flat

- status: fails
- tags: fn_801FC7F8,regalloc,r0,vreg-numbering
- scope: RPSports_801fc7f8
- source: claude/x-fc7f8-1029

symptom: target limit r0 / flag load r3; ours limit r34->r4, flag temp r54->r0 (coloured first), base r53->r3
cause: target needs number(limit) > number(flag temp). Named and inline @ vars are numbered below codegen temps; ternary temp allocated before its condition (53<55); single-use flag local/inline param substituted by front-end; dead flag var dropped
fix: failed: inline limit getter, inline flag param, nested mode getter, multi-return inline, register limit, bool flag local, uninit flag + separate assignment, (flag = load) == 0, flag loaded before limit=1500, ternary ==0?1200:1500. All 12 lines
