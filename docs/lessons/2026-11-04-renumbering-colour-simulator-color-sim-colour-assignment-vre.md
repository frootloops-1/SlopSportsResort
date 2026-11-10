# Renumbering colour simulator: color_sim + colour assignment + 'vreg=float' renumbering predicts which vreg position closes a colour wall

- status: works
- tags: tooling,color_sim,colour
- scope: Pack
- source: claude/sp801f1-1104

symptom: need to know which vreg number a named/inline value must have before trying source shapes
cause: MWCC colours callee-saved nodes with the lowest already-used register not taken by a neighbour, else the highest free; order = reversed simplify stack
fix: scratch/csim.py in sp801f1-1104 (load via tools/color_sim.load, sort with renumber map, assign as above): reproduced SpMdlSetB/SpMdlSet/SpMdlSetD actual colours exactly; SetD needs mgr/anm numbered in (46,52) of the D_d dump, i.e. between the i*4 IV and the screen/cap temps, which source order cannot reach
