# ef_animcurve U8 expression duplication and next loop helper regress

- status: fails
- tags: ef_animcurve,U8,register-allocation,inline
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Need demote rangeSize and nextLoop below parameter clique without losing early computation.
cause: Direct expressions do not hoist across all random branches; next-loop helper/reference changes inline identities and code shape without meeting score gate.
fix: ALL5 count*2 expressions: 96.97059/895 lines, +7 slwi net; reverted. After reference win, inferred next-loop helper returning const-ref snapshot: 97.83865/368 lines vs 98.768906/382; lower raw line count is insufficient when verify regresses. Reverted; no helper retained.
