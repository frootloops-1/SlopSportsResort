# Sub-object calls at self+off CSE'd into saved reg: declare as u8 array members

- status: works
- tags: cse,struct
- scope: RPGol_802b8568
- source: fn_802B888C

symptom: addi per call missing; pointer kept in saved reg
cause: (u8*)self+off expression CSE
fix: declare u8 s14[0x50], s64[0x50] members and pass self->s14
