# FPR order reversed in copy-then-subtract: load into locals, store each immediately

- status: works
- tags: fpr,regalloc,vec
- source: RPBsb_80258768 fn_80258978

symptom: out->x=m03;..;out->x-=p.x pattern: f3/f2/f1 reversed vs orig f1/f2/f3 (98.1)
cause: orig keeps loaded values in registers for the subtraction instead of reloading out->x
fix: f32 x=..;out->x=x; f32 y=..;out->y=y; ... out->x=x-p.x (interleaved decl+store; all-loads-first gives schedule diff)
