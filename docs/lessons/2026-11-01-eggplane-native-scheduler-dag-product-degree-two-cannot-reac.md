# eggPlane native scheduler DAG: product degree two cannot reach retail f4 by renumbering; no source gain

- status: fails
- tags: egg,plane,scheduler,fpr,interference,compiler
- scope: egg/geom/eggPlane
- source: codex-eggplane-1101, base 2cd5432ac

symptom: project remains 73.17073%, multScalar 100%; no source improvement.
cause: Native scheduler DAG tracing shows dot(input) float loads height 14 versus int copy loads height 4. The input-form product f36 has only FPR neighbours f37/f38; no pure renumbering of that graph can force lowest-free colour f4. Debugger-only PCode reorder extends product overlap through normal.z and input.z and reproduces retail FPRs, but final scheduling still differs. This diagnostic is not a source match. Boundary, scalar-capture/helper, base-copy, IEEE, propagation/CSE/lifetime and extra-CPU probes all fail; six GC builds agree for each compilable source. __builtin_memcpy not recognized.
fix: No source/header/config/marker retained. Read-only reusable tools/mwcc_sched_trace.py records graphs, priorities, can_issue outcomes and choices with normal backend dumps and wrapper lock. Smoke trace reproduces all four original work-form graph snapshots exactly. Evidence: /private/tmp/ogws-eggplane-1101/build/evidence/eggplane-scheduler/. Park until original copy/inline semantics can explain both overlap and final memory/scheduling constraints. Configured DOL 0 excludes Plane; unit remains NonMatching.
