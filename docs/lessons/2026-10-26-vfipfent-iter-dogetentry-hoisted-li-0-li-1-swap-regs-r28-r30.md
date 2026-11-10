# VFiPFENT_ITER_DoGetEntry: hoisted li 0 / li -1 swap regs (r28/r30) not an IMM/struct issue

- status: fails
- tags: vf,pf_entry_iterator,regalloc,hoisted-constant
- scope: src/revolution/VF/pf_entry_iterator.c

symptom: 6 IMM-bucket diffs: li r28,0/li r30,-1 vs ours li r28,-1/li r30,0 plus stw uses; displacements identical
cause: Two inlined IteratorInitialize sites hoist constants 0,1,-1,3 into callee-saved regs; coloring order of 0 vs -1 differs (use counts equal at 2 each; 3 has 1 use yet gets r31 so not use-count priority)
fix: Tried: reorder name_len=0 vs start_cluster load (no change); move file_sector_index=-1 store after offset_mask (regresses). Parked.
