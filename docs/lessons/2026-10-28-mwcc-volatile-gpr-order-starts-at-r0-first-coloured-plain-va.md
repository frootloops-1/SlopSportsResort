# MWCC volatile GPR order starts at r0; first-coloured plain value takes r0 (probe-verified)

- status: works
- tags: regalloc,r0,colouring,probe
- scope: all units
- source: docs/forecast-regalloc-notes.md; Melee regalloc_explain.py

symptom: r0 vs rN register diffs: unclear which value the target colours first
cause: Volatile GPR order is r0,r3-r12; descending vreg colouring gives r0 to the first-coloured plain-ALU value; load/store base values never take r0
fix: Read an r0-vs-rN diff as a colouring-order difference (target's r0 value has the higher vreg); steer via local declaration order/type (forecast-regalloc-notes levers). Verified with scratch probes on GC/3.0a5.2.
