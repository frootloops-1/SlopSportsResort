# alpha = f(self->frame); self->frame-- after call fixes register colouring

- status: works
- tags: mwcc,register,decrement
- source: RPUtl_801C9E7C

symptom: frame value r5 vs r6, 0xff in r4 vs r0
cause: local copy of frame + pre-decrement before helper call
fix: pass self->frame directly, decrement after the call statement
