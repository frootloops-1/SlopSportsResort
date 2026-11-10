# fn_802CC374 (RPBox_802cb9cc): 1-trip inner loop must index self->score[1][i] directly

- status: open
- tags: rpbox,unroll,induction-pointer
- source: tb-cb9cc-20261031

symptom: baseline used a separate score pointer (two induction pointers); plain loop fully unrolls even with opt_unroll_loops off
cause: unroll pragma alone ineffective; inner 1-trip loop blocks it; direct self->score[1][i] gives single pointer
fix: 96.6; remaining GPR numbering (lo/hi vregs need to be numbered after hoisted consts). Failed: decl order, lo=lo+1, branch order, u32/!=/const bound, do-while (loses ctr)
