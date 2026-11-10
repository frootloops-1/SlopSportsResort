# eggPlane project: no sibling shape in game, flags and definition order do not move it

- status: fails
- tags: egg,plane,flags,siblings
- scope: egg/geom/eggPlane
- source: orchestrator 2026-10-27

symptom: project stays 73.2% (ratio 0.683 vs orig body)
cause: Scan of all 1146 orig asm files finds no other function with int struct copy interleaved with fmuls/fmadds dot; -O3/-O2/-O4,s, -inline deferred/noauto/level=2, -opt space/schedule, -ipa off, and defining project before multScalar all give identical output; fp_contract off and nopeephole worse
fix: None; remaining unexplored: block-boundary tricks around the copy, Ghidra pcode evidence
