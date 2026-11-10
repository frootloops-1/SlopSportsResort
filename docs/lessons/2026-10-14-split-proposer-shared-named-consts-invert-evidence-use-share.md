# Split proposer: shared named consts invert evidence; use --shared

- status: works
- tags: splits,propose_splits,sdata2,sbss
- scope: RPGolScene blob 0x802A79F8-0x802B614C

symptom: propose_splits reports dozens of 'conflict' notes and only low cuts because a few literals are used across the whole blob (last user = a late fn)
cause: Those literals are named extern const globals (one TU defines, others reference), not TU-local pool entries
fix: Find literals whose users span many TUs, pass them via --shared; conflicts vanish and hidden cuts appear. Also: each 4-byte .sbss singleton padded to 8 is its own TU, and its create/destroy pair (stw to the slot) plus ctor/dtor/this-adjust thunks mark the TU end. Use --cuts to compute section ranges for a hand-checked cut set
