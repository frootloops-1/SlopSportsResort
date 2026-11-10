# MWCC spill choice: fewest weighted uses first, loop uses count, ties to lowest vreg (probe-verified)

- status: works
- tags: regalloc,spill,probe
- scope: all units
- source: docs/forecast-regalloc-notes.md

symptom: Which value spills when more than 18 values are live across calls
cause: Spill score is flow_weight*(2*uses+defs)/degree; lowest score spills; probes: 1-use then 2-use then 4-use values spilled; a 1-use in-loop value was kept over a 2-use straight-line value
fix: Only relevant for units with more than 18 live-across-call values; to move a spill, change the use count or loop placement of the value, not declaration order.
