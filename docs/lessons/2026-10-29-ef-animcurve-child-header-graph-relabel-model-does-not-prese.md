# ef_animcurve Child header graph relabel model does not preserve actual source graph

- status: fails
- tags: ef_animcurve,Child,register-allocation,graph
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Particle-phase trial adds fresh header but its colour is r22, name31; synthetic relabel header70->66 predicts header first.
cause: Actual source declaration movement changes more graph identities/coalescing than a single synthetic node relabel; old command remains live for both frame helpers, adding two mr.
fix: Particle phase 97.51491/704 lines; modeled header-after-frame1 declaration 97.29128/796 (+2 mr). Both reverted against97.88188 baseline. Future hypothesis: frame helpers both consume header cast to remove old saved command lifetime, but not tried under two-no-gain bound.
