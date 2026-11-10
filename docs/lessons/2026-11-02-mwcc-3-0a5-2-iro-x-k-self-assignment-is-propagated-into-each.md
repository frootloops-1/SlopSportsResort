# MWCC 3.0a5.2 IRO: x += K self-assignment is propagated into each use (PropagateSelfAssignments), not CSE'd

- status: works
- tags: IRO,CSE,PropagateSelfAssignments,numbering,mwcc_frontend_trace
- source: gol441c2-1102-opus

symptom: want a load in a var: int d = p->f; d += K; then two uses of d
cause: stage 022 PropagateSelfAssignments rewrites both uses to d+K (d keeps 2 uses so the lhz lands directly in d's vreg), but d+K is cheap so CommonSubs does not CSE it; codegen emits it twice, backend merges into a high codegen temp coloured first
fix: use to put a load into a named/@var register; expect the +K value to become a codegen temp
