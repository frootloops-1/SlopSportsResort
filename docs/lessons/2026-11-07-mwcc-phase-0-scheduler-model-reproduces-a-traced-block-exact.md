# MWCC phase-0 scheduler model reproduces a traced block exactly (deps + select rules)

- status: works
- tags: scheduler,select_ready_node,sim,fn_8031A0E0,RPBow_80319C98
- scope: RPBow_80319C98/fn_8031A0E0
- source: claude/bow-80319C98-1105 round 6

symptom: Pre-RA schedule walls need many 1.5-min traces per what-if
cause: Graph = RAW producer latency, WAR/WAW 0, overlapping store->load/load->store producer latency, all->bl 0; height=max(lat,max(d+h(succ))), latest=hmax-h. Issue: 1 LSU + 1 FPU per cycle, no store the cycle after a store, an LSU op issued at exactly its earliest cycle ends the cycle (fitted); priority urgency>#succ pending==1>height>lower rank>list order
fix: ~/Downloads/ogws-tools/mwcc-sched-sim (deps.py, sim.py, fast_trace.py, ex4.py add/remove-edge search): one trace, then test list orders and extra/removed edges offline in ms. Phase-1 (post-RA) rules not reproduced (e.g. nothing issues after a ps_mr at its earliest cycle).
