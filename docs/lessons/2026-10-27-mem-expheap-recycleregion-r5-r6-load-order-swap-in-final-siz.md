# mem_expHeap RecycleRegion_: r5/r6 load-order swap in final size check is a colouring wall

- status: fails
- tags: mem_expHeap,RecycleRegion_,register,F5,wall
- scope: revolution/MEM/mem_expHeap
- source: orchestrator-1027

symptom: 99.20%, 30 differing lines. Target: lwz r6,0xc(r1); lwz r5,0x8(r1); subf r0,r5,r6; ours loads 0x8 into r6 then 0xc into r5, so inlined InitMBlock_ uses r6 as mblock instead of r5
cause: scheduling/colouring of the freeRegion start/end loads after the prev-merge block; first divergence follows 'mr r8,r5'
fix: failed (~40 earlier variants plus this round): u32 cast on GetOffsetFromPtr, raw GetUIntPtr(end)-GetUIntPtr(start), reading end then start into locals. Parked; only permuter or a different inline shape for the size check untried.
