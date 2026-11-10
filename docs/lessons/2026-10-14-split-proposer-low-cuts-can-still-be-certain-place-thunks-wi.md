# Split proposer: low cuts can still be certain; place thunks with their target TU

- status: works
- tags: splits,propose_splits,thunks
- scope: RPTnsScene blob 0x80214480-0x8024E334

symptom: propose_splits rates 29/59 cuts low, but every cut has a [high] window; one sinit cut leaves this-adjust thunks (subi r3; b) in the next TU
cause: low = tie on position inside the window, not doubt about existence; sinit trailer allowance (8 fns) is shorter than a long thunk run
fix: Check each cut has a [high] evidence line, apply all; move cuts so 2-insn thunks sit with their branch target's TU and single-vtable members with the vtable owner's TU; then --cuts for section ranges
