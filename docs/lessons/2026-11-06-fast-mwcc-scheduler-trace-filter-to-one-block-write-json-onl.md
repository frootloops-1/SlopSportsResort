# Fast mwcc scheduler trace: filter to one block, write JSON only at graph events (~1 min instead of >30)

- status: works
- tags: scheduler,mwcc_sched_trace,tooling
- scope: general
- source: scratch fast_trace.py, RPBow_8033B690 2026-11-05

symptom: tools/mwcc_sched_trace.py rewrites the whole scheduler.json on every event; a 700-insn function took >30 min
cause: O(n^2) JSON rewriting plus full candidate lists for every block
fix: Copy the tool, make sched_event record only when the graph's asm matches a block signature (e.g. ps_sum0+fabs+fcmpo), skip candidate/eligibility hooks otherwise, flush at the next graph event. Phase 1 (post-RA) graphs carry register WAR/WAW edges whose heights decide ties; compare phase-0 and phase-1 picks with an eligible-candidate dump (latest, released succ, height, rank).
