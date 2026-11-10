# RPGrpModelRfl DrawGX: stw spDrawModel slot vs lbzx/lhz scheduler tie-break (no source order reaches retail)

- status: fails
- tags: DrawGX,scheduler,tie-break,RPGrpModelRfl
- scope: Pack/RPGraphics/RPGrpModelRfl
- source: step2 2026-11-01

symptom: 99.7%, 2 lines: retail emits lwz 0x94(r3); li r4,TBL; lis r22; stw spDrawModel; lbzx; addi r22; stb 0xc(r22); lhz 0x90(r3); ours puts the stw after lbzx and addi
cause: Scheduler.c select_ready_coloring_node prefers the instruction that frees a dependent it alone blocks, then critical-path height. The stw reaches the retail slot only if mFlagsRfl is read into a local before the tevStageNum store, but then addi precedes lbzx and lhz floats above stb 0xc (net worse). Contradicts the 10-30 latency model: the constraint comes from the indexed lbzx table load and the lhz
fix: none. Swept ~35 orderings; dead: do/while(0) or goto between store and lookup (merged before scheduling), separate if store (extra cmp/branch), reverseCulling via spDrawModel (forwarded), index casts u32/s32/ptr-arith identical, u8/u16 add clrlwi, store-last, flags local before the store. Next: get the compiler dump where the gdb stub can bind (pre-schedule PCode order + per-instruction memory flags), check whether lbzx comes from AddPropagation (lbz->lbzx with the pointer-op flag) and, if retail lbzx is not a pointer op, find a source form where codegen emits the indexed load directly. Unit otherwise 38/39, all other sections 100; a temp Matching link showed 12 differing bytes all in DrawGX
