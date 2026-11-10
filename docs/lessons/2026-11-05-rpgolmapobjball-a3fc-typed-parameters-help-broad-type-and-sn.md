# RPGolMapObjBall A3FC: typed parameters help, broad type and snapshot sweeps stall

- status: open
- tags: regalloc,copy,RPGolMapObjBall
- scope: fn_8029A3FC
- source: codex-golball-1105

symptom: A3FC 89.65%, 500 vs 496 bytes; saved d/src/flag registers and second scalar-copy FPRs differ.
cause: Named pointer locals displace incoming parameters; second block float declaration order reverses target FPR allocation. First block still has wrong load-temp identities and loop index/offset priority.
fix: Use GolBallCopy*/const GolBallCopy* parameters directly, reverse only second block float declarations: 93.008%, 496 bytes. More than 80 first-block type/init/group/snapshot/helper and loop variants produced no full match; typed ABI cleaner than repeated casts, helper not retained. Remaining first scalar copy and loop register allocation need a new hypothesis.
