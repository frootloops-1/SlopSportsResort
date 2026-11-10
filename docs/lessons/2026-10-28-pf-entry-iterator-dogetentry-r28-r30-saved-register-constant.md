# pf_entry_iterator DoGetEntry r28/r30: saved-register constants are coloured by descending creation order (debugger)

- status: open
- tags: pf_entry_iterator,mwcc-debugger,regalloc,constants,inline
- source: backend-00/02 + regalloc dump via gc30 run_unit_fn.sh

symptom: li r28,-1 / li r30,0 where target has li r28,0 / li r30,-1 (r29=1, r31=3 match); 12 diff lines, 2 inline sites
cause: Allocator colours the loop-invariant constant vregs in descending vreg number (all costs 0): r160(3)->r31, then 0,1,-1 by REVERSE creation order. Creation order comes from the inlined IteratorInitialize/DoMoveTo statement order: ours -1 (file_sector_index), 1 (1<<log2), 0 (index store); target needs 0 first, then 1, then -1. Swapping the -1/mask stores gave 1,-1,0 (confirms model, 18 diff lines).
fix: Not fixed. Tried: store order in IteratorInitialize, named zero locals, (u32)0, index=param first (bad), name_len=0 moved earlier (226 diff lines). Need a natural construct that creates constant 0 before 1<<log2 in the first inline site, with -1 last.
