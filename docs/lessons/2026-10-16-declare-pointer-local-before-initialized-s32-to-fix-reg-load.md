# declare pointer local before initialized s32 to fix reg/load order

- status: works
- tags: regalloc,load-order,rpbsb
- source: RPBsb_8028a2e8 2026-10-16

symptom: two callee-saved locals swapped regs / wrong lwz order
cause: declaration+initializer order drives allocation
fix: T* b; s32 a = x->a; b = x->b;
