# Golf field: psq asm add, loop stride, bool helpers, dtor if-depth

- status: works
- tags: RPGolFieldManager,psq,loop,dtor

symptom: nw4r/math.h clashes with file PSMTX decls; loop regs wrong with explicit stride off; float compare result not materialised
cause: header conflict; explicit off var
fix: local asm psq_l/ps_add; index base+i*stride; static inline bool Less(a,b); dtors: 2-3 nested if(self)
