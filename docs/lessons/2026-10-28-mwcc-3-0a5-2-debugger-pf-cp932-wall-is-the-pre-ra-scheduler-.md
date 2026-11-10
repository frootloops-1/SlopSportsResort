# MWCC 3.0a5.2 debugger: pf_cp932 wall is the pre-RA scheduler hoisting li r3,1, which forbids r3 for the temp

- status: open
- tags: pf_cp932,mwcc-debugger,scheduler,regalloc
- source: docs/mwcc-debugger.md

symptom: OEM2Unicode/Unicode2OEM: li r3,1 placed before the last ALU/store and the temp lands in r5 (target: temp in r3, li after the store)
cause: backend-01 (after optimizer) already has the target order; the pre-RA scheduler moves li r3,1 up (backend-02). Allocator then sees a precoloured r3 write inside the temp's live range (r50 neighbours include r3) and cannot use r3. Obtained with ~/Downloads/mwcc-debugger gc30 port.
fix: Not fixed. Next: find source changes that alter the pre-scheduling block (compare backend-01) so the scheduler leaves li r3,1 after the store; use the debugger to test each variant (1-2 min each).
