# resort bowling: RPBowTrajectoryGuide::Draw 99.96 f28/f29 swap for nCosAngle

- status: open
- tags: resort,bowling

symptom: 2-byte DOL diff on flip
cause: float register allocation
fix: moving fneg / inlining -cos both worse; remaining wall
