# forecast lever 8 (named float result) closes fn_801F0020

- status: works
- tags: forecast,regalloc,float-local,fctiwz,RPSports_801ef064,fn_801F0020
- scope: fn_801F0020
- source: forecast-regalloc

symptom: fn_801F0020 99.9%: (s32)fn() - self->f30 had the fctiwz stack-reload in r4 and the field load in r0 (target: r0/r4 swapped, subf operands swapped)
cause: with the conversion inside the expression, the int temp is newer than the field-load temp; naming the f32 call result moves the fctiwz to the subtraction and changes vreg age
fix: f32 fb = fn_801F8360(...); shown = fn_801F938C(lbl, (f32)((s32)fb - self->f30)); -> 100%. Failed: s32 named result (decl inline or up front), -f30+best, best -= f30, -(f30-x), named s32 cur for f30 (any decl order)
