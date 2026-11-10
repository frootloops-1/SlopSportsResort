# fn_802C7D08 (RPBox_802c7924): member reload after an aliasing store is an expression temp coloured before the CSE'd pool constants; name it and write the divide in the call arg

- status: works
- tags: regalloc,fpr,fmuls
- scope: RPBox_802c7924 fn_802C7D08
- source: FPR batch 2 2026-10-28

symptom: fn_802C7D08 99.64: pool constants 0.0/1.0 on f2/f1 (target f1/f0), reload and quotient in different regs, fmuls operands swapped
cause: reload of self->f3C is an expression temp coloured before the CSE'd constants; MWCC canonicalises commutative fmuls operand order so swapping source operands does nothing, it follows vreg class
fix: mag = self->f3C; BoxScale(&n,&v,BOX_ONE/mag) (named local reused from k, divide in the inline arg) and a named local w = BOX_ONE - b->f60 declared AFTER ax/az with b->f60*az - w*ax; 100%, no marker
