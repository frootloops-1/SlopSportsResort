# fn_80281A88/fn_80281DA0 (RPBsb_802817a0): FPR walls, loop copy removes frsp but regresses score

- status: fails
- tags: fpr,scheduling,frsp,RPBsb_802817a0

symptom: fn_80281A88 97.3: frsp+forwarded m2[0][0] in copyMtx(&m2); target reloads from stack, loads all 11 values before stores (more FPRs live). fn_80281DA0 99.7: diff in f3 and fctiwz f2,f1 in target vs f2 and f1,f1 in ours
cause: A88: writing m2[i][j<2]=m[i][j] as a nested loop drops the frsp (lesson 2026-10-26) but score falls 97.3->96.4 (schedule still source-order, fewer FPRs). DA0: target needs score still live across its fctiwz (tmpA cannot share f1)
fix: dead A88: nested loop for cols 0-1, dir/pa columns as loops or setBase, [0][0] last, temp var; dead DA0: si/di locals, swapped order, += form, diff-declared-first, score init at top/late, (void)score. Unit otherwise needs these two only
