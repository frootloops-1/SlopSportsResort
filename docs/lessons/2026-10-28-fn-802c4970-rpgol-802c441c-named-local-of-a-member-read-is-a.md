# fn_802C4970 (RPGol_802c441c): named local of a member read is an older vreg; pass the field directly as the call argument

- status: works
- tags: regalloc,fpr
- scope: RPGol_802c441c fn_802C4970
- source: FPR batch 2 2026-10-28

symptom: 99.92: volatile f3/f5 swap in the golRemap call
cause: named local lo = self->f6C is an older vreg (coloured later -> higher volatile); as a call-argument expression it is a newer temp
fix: removed `float lo = self->f6C;`, pass self->f6C directly into golRemap(0.0f, end, ..., hi, diff); 100%, no marker
