# ef_animcurve U8 identities vanish at expression propagation; alias guard becomes stack storage

- status: fails
- tags: ef_animcurve,U8,compiler-trace,IRO,register-allocation
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: U8 remains 99.58403 with 20 changed lines. Named negative0/combined0 outputs compile flat, although an unchanged-graph renumbering model predicts the desired registers.
cause: Native trace: both objects have two references after inlining and through scalarization/copy propagation. IRO_ExpressionPropagation substitutes their single reads, leaving one store reference each; IRO_DeadStore then removes them. Corresponding signed accesses retain the frontend objects but make them stack-backed. Backend optimization forwards/removes the stores and reloads, leaving anonymous vregs 322/325. In this probe the memory objects never become the old named GPR identities required by the model.
fix: No game-source change retained. Multiple-use probe regressed to 97.30252 and changed opcode shape. Signed-access probe regressed to 97.38403 with two extra lbz; explicit flag0 reuse removes those loads but still scores 97.30420 with 516 changed lines. The real graph changes too: flag0 takes r4, v0 r6, interp r8, k1/v1 r7. All reverted. Added tools/mwcc_frontend_trace.py with exact compiler SHA1 guard and native GC3 layouts. Regenerated evidence and zero decoder-error checks are in primary build/evidence/ef-trace-20261030, outside disposable worktrees. Copies/output references alone cannot preserve these identities; preserving frontend names is not sufficient.
