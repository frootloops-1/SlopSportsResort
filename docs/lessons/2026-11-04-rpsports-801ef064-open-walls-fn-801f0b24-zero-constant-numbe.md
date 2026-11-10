# RPSports_801ef064 open walls: fn_801F0B24 zero-constant numbering, fn_801EF2F0 param degree K, fn_801EF4B8 last after col temp

- status: open
- tags: regalloc,color_sim,fpr_replay,RPSports_801ef064
- scope: Pack/RPSports/RPSportsCommon/RPSports_801ef064
- source: claude/sp801ef-1103

symptom: 0B24 88.8 (self/IV/counter/zero order), 2F0 98.6 (width f29/margin f30/square f31 in retail), 4B8 99.5 (last r28/col r27/xor r26 in retail)
cause: 0B24: color_sim search: only renumbering the merged li 0 (vreg 41) to between lis 0x4330 (48) and li 1 (50) i.e. init()'s own zero gives the target. 2F0: width/margin have degree 32=K so are set aside in sweep 2 and coloured first; retail needs their degree <32 (no single edge removal or renumbering reaches it; volatiles differ too). 4B8: named last (38) must be numbered above the col-word temp (57)
fix: FAILED: 0B24 loop body as static inline helper (fn_80200A88 recipe) no change, zero passed as inline param no change; 2F0 VEC2/VEC3 ctors, nw4r VEC2Len, whole body as inline helper (worse), statement orders (only fixes pool); 4B8 dropping last, 4 declaration placements, last2=last (all worse)
