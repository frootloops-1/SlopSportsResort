# x = x * K emitted fmuls K,x: use x *= K

- status: works
- tags: float,fmuls,operand-order
- scope: RPTns
- source: RPTns_80222a70

symptom: fmuls f0,f0,f1 instead of f0,f1,f0 for field*const store
cause: x = x * K canonicalised differently from compound assign
fix: self->f218 *= 0.5f; (fn_80223A28)
