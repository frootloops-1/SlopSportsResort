# CSE temp creation order: name a later-used row pointer early to colour its index temp first

- status: works
- tags: A0E0,RPBow,gpr,cse,regalloc
- scope: fn_8031A0E0
- source: round 11

symptom: (j+1)*16 vs base+k*16 GPR swap (r7/r8)
cause: IRO numbers CSE temps in reverse creation order (created at 2nd occurrence); P.y's row k forms base+k*16 before P.z's j+1 row
fix: BowExcelGlobal* rz = BowCamT4Row(res, j + 1); after P.x += and before P.y, used in P.z (R17 399); other placements (before P.x, used in P.x too) lose an insn
