# Two-def bool coloured first: value-context || via local pointer becomes a codegen temp

- status: works
- tags: colouring,bool,ELOR,IRO,mwcc_dbg,RPGol,fn_802926EC
- scope: Pack/RPSports/RPGolScene/RPGolFieldManager
- source: golfield-fn-1102

symptom: li 0 / conditional li 1 bool lands in a nonvolatile (r27) or r0; target has r3 and neighbouring codegen temps skip r3
cause: if-assign bools and inline-returned bools are IRO/front-end vars (numbered below every codegen temp, coloured last). IRO RebuildLogicalExpressions only rebuilds a value-context ELOR whose operands read a surviving local (bool b = p->x == 5 || p->x == 8 with GolSing* p = global); codegen then materialises it in a fresh high vreg (li 0 / bt / bf / li 1) that is coloured first, and the operand load is a codegen temp above it
fix: GolSing* sg = lbl_804BF8C4; bool stB = sg->state == 5 || sg->state == 8; if (!stB && ...). Check with mwcc_dbg: a vreg >= first codegen number with two li defs in backend-00
