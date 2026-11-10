# RPGrpModelRfl::DrawGX stw spDrawModel slot: static const-self form, store reorders, pointer locals and real-type probes all fail; wall is local to the block

- status: fails
- tags: RPGrpModelRfl,DrawGX,stw,scheduling,spDrawModel
- scope: Pack/RPGraphics/RPGrpModelRfl DrawGX 0x801B5178

symptom: retail: lwz 0x94, li, lis, stw spDrawModel, lbzx, addi, stb; ours: lwz, li, lis, lbzx, addi, stw, stb (99.7%, 2 lines)
cause: Not a const/this issue: static DrawGX(const RPGrpModelRfl* self,...) with const_cast store gives identical 2-line diff. Truncating the function after the first bVar4 block (return after the store), simplifying bVar4/bVar6/useMat conditions, and probes with real class types vs plain structs all reproduce our order, so the wall is local to the 4-store block (type load, spDrawModel store, tev store, reverseCulling store). In a probe with a const param all loads (incl. lhz mFlagsRfl) hoist, which retail does not do, so retail's this is non-const. Permuting T/P/V/R statement order: P-first puts stw before lwz; T,P,R,V puts stw right after lis but moves the rev store before the tev store; T,P,V,R equals our current output. Pointer/reference locals for sDrawCoreSetting do not change it.
fix: open: no source form found. Experiment patch kept in session scratchpad (static-drawgx-experiment.patch). Remaining ideas: unknown inline that the store lives in, or Ghidra caller/xref evidence for member vs static; otherwise needs MATCH-PENDING (R17) with owner OK.
