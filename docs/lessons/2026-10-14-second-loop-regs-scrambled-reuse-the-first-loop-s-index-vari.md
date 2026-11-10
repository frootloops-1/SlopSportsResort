# Second loop regs scrambled: reuse the first loop's index variable

- status: works
- tags: regalloc,loop,variable-reuse
- scope: RPTns_8022f2b8
- source: opus worker 2026-10-14

symptom: pole loop counter/pointer regs wrong after an entity loop
cause: orig reused one int i for both loops
fix: int i; i = n-1; ...; i = 1; do { T* md = self->mdl[i]; Init(md); } while(--i>=0); (fn_80230280)
