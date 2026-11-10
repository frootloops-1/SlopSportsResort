# Missing callee-saved reg: a late local shares a dead local's register

- status: works
- tags: regalloc,callee-saved,declaration
- scope: RPTns_8023bd9c
- source: opus worker 2026-10-14

symptom: orig saves one more reg (self in lowest), ours fewer and smaller
cause: late-declared local reuses self's reg after self's last use
fix: declare that local at the function top (fn_8023C4C8)
