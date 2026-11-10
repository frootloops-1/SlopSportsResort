# fn_802C531C: 64->18 lines via getter shots, local-pointer bool in golFollowT, zero-literal-first remap

- status: works
- tags: colouring,getter,bool,fpr,RPGol,fn_802C531C
- scope: Pack/RPSports/RPGolScene/RPGol_802c441c
- source: gol441c2-1102

symptom: four volatile GPR pairs + one FPR pair swapped, target colours inline values before codegen temps
cause: inline-return bools are front-end vars (below codegen temps); named shots is below inline-expansion v; in remap in0 and 0.0f literal are codegen temps created in source order, higher vreg colours first
fix: shots = golShotCount(st) (inline getter, R17 row 82); in golFollowT GolStateView* sg = lbl_804BF8C4; bool stB = sg->state==5||sg->state==8; if (stB) (bool becomes codegen temp); remap: float d = in1; if (0.0f == (d -= in0)) so the zero literal is created before the in0 load. Remaining: golShotKindB bit-test ELOR bool stays a front-end var (local pointer, ret var, param f, order, switch, ternary all identical or worse).
