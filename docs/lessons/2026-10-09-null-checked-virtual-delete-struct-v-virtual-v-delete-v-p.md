# Null-checked virtual delete: struct V{virtual ~V();}; delete (V*)p

- status: works
- tags: RPGolFieldManager,vtable

symptom: manual vtable fn-ptr cast uses wrong register (99.4%)
cause: CW register choice differs
fix: delete (GolVBase*)p with virtual dtor gives lwz r12,0(r3); lwz r12,8(r12); mtctr
