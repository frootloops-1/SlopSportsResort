# MWCC select_ready_node (0x599920) order: urgency, released-succ count, height, opcode rank (phase 0), list order; fn_80323F30 target infeasible under first-use IR

- status: fails
- tags: scheduler,select_ready_node,tie-break,fn_80323F30,RPBow_80323790,rank
- scope: RPBow_80323790/fn_80323F30
- source: claude/bow-80323790-1105

symptom: fn_80323F30 98.4: block after stb 0x245 needs pool loads 0.03,0.9995,0.007,0.02,0.9982,-197,191,192,0.008,0.009,singles then zero stores; ours 0.03,0.007,0.9995,0.02,0.008,0.009,..., zero stores interleaved
cause: Disassembly of select_ready_node @0x599920: first eligible node (pending 0, earliest<=cycle, can_issue), then for each later node: urgency (latest<=cycle), count of successors with pending==1, height, then only when virtual flag [0x710394] set (phase 0) lower opcode rank (stfs/stb/stw 1 < lfs/lwz 3 < li 4, mr 0), else list order. Colour = vreg number descending, lowest free; vreg number = first-use position (dup literal loads are CSEd to the first). With static counts the target needs c(0.9995)>c(0.007)>c(0.02) (0.9995 has only 3 stores) - infeasible; height split would reorder the stores. Phase 1 (post-RA) reschedules every block with phase-0 output as list order and no rank, so it cannot create the order either.
fix: None. Dead: loop for the 0.007 stores, chained A=B=v pair stores, local f32* bases for the arrays (all identical); zeroing loop for A/B (zero stores move ahead, 94.0); named const locals (decl first-use, assign target order: whole-function recolour 95.7 + pcode DSE deletes zero stores since no pool load intervenes); volatile on 0.007/0.008/0.009/0.9995 stores (breaks literal CSE, 90.9-97.1). mwcc_sched_trace on this unit runs >30 min (use a 2 h background timeout). Only remaining lever: R17 scheduled-asm body (big: 390 insns, 18 FPR saves, @N pool literals would need named consts).
