# Operand order of zero + x: write (inverseMass + zero) when target is fadds f0,x,zero

- status: works
- tags: fadds,operand-swap

symptom: fadds f0,f0,f27 vs f27,f0 (1 line diff)
cause: commutative operand order follows source
fix: swap the source operands: (inverseMass + zero) (fn_801C5240 99.99->100)
