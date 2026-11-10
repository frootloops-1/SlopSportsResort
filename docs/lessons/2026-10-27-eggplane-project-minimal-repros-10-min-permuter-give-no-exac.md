# eggPlane project: minimal repros + 10 min permuter give no exact or authentic state

- status: fails
- tags: egg,plane,permuter,scheduling
- scope: egg/geom/eggPlane
- source: orchestrator 2026-10-27

symptom: project stuck 73.2%
cause: Plain-struct repros: int struct copy-construct (lwz/stw, even POD) in block -> plain 3-reg dot; float memberwise copy (assignment) hoists loads but CSEs v loads (orig loads v.y as float AND int). Permuter (10 min, -j6, 1610->910 best) best states are semantically broken (dot on uninitialised work via goto) or the known dot(rVec) form
fix: None; remaining route is reading mwcc scheduler (Ghidra on mwcceppc.exe)
