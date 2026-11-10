# eggPlane project: Ghidra decompile and class-layout variants give nothing new

- status: fails
- tags: egg,plane,ghidra,layout
- scope: egg/geom/eggPlane
- source: orchestrator 2026-10-27

symptom: project stuck at 73.2%
cause: Ghidra decompile of 0x800A2074 only restates dataflow (v.y loaded as float and as int, dot = nz*vz+nx*vx+ny*vy fmadds order, copy to r3, multScalar(scale, &tmp), then 3 subs); no structural hint. mutable normal member, Plane3f derived from Vector3f (dot/multScalar on this), dot(rVec) vs dot(work) all compile to the same two schedules as before
fix: None; remaining blocker is scheduler: orig has early-load f0-f4 dot pattern WITH int copy in block
