# VFiPFENT_ITER_DoGetEntry is a register-colour swap of hoisted loop constants, not an immediate problem

- status: fails
- tags: pf_entry_iterator,VF,F4,register,wall
- scope: revolution/VF/pf_entry_iterator
- source: orchestrator-1027

symptom: 99.94%, 6 lines: target li r28,0 / li r30,-1 (r29=1, r31=3); ours r28=-1, r30=0. Other 4 lines are the stw regs at the two inlined IteratorInitialize sites
cause: hoisted constants appear coloured in reverse creation order, 3 first and 0 always second; target needs 0 created before 1 before -1
fix: failed: swap -1 and offset_mask stores (regresses; gives r28=1,r29=-1,r30=0, 0 stays r30), named u32 zero=0 for both calls (folded), name_len=0 before first IteratorInitialize (98.1). Untried: loop shape (for vs do-while), IteratorInitialize defined before DoGetEntry in file, permuter.
