# fn_802C5C78: abs-arg eval order decides which dot gets f31 and its schedule order

- status: open
- tags: fpr,regalloc,RPGol_802c58d4,fn_802C5C78

symptom: y/sq callee-saved FPR swap (orig y=f31,sq=f30,x=f29; ours y=f30,sq=f31,x=f29)
cause: mwcc_dbg: dist and t colour first; the rest colour by descending vreg number; abs(y) temp is created after the sq temp so it colours after sq. Evaluating golAbs(x) first (golDist(len, ay, ax) + golAbs(y), golAbs(x)) and putting the m+3 dot statement first gives sq=f30 but mirrors the dot schedule (x=f31,y=f29): 84 -> 76 diff lines
fix: no full fix: regsearch --generic 3k evals no gain; 96-variant grid (decl order, dot stmt order, sq position, abs eval order, x/y naming) no exact; FSqrt inline identical; sq as inline param/no named sq moves fmuls late (97.1)
