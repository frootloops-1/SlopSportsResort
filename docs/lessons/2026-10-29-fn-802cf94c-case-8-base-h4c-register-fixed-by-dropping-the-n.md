# fn_802CF94C: case 8 base h4C register fixed by dropping the named BoxPl* o local

- status: works
- tags: RPBox_802cf93c,regalloc,mwcc_dbg
- scope: RPBox

symptom: base (lha 0x4c) r7 vs target r8; o/idx/ptr r6/r5/r8 vs target r5/r6/r7; FPR lerp f2/f5 swap
cause: named o (declared in case block) had a lower vreg than base, so base coloured first
fix: u=self->owner->f3CC; k=BoxPlGet(self->owner,self->owner->w3D4)->w2F4: 36->28 lines (99.8->99.9). Remaining o coloured after idx/ptr (r7 vs r5); failed: BoxCurP inline, nested BoxPlGet, BoxPlAt(pl,i), base declared last, BoxLerp for the case-8 lerp (44 lines)
