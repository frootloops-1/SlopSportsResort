# eggPlane scalar lifetime references and copy-dot boundaries give no gain

- status: fails
- tags: eggplane,project,scheduler,lifetime,copy,inline
- scope: egg/geom/eggPlane
- source: codex-eggplane-20261102, main 9b995ee06

symptom: multScalar exact; project 73.17073%, .text 78.43137%; one of two functions exact.
cause: Fifteen scalar-lifetime probes (component/product/dot const references before or after copying, aggregate captures) do not create retail FPR overlap and scheduling; best 66.92683%. Ten combined copy-dot value/ref/aggregate/input-view helper probes scalarize the integer copy or add intermediate copies; best 53.26829%. All 25 were compiled across six GC versions with no compiler-dependent improvement.
fix: Restored source byte-for-byte, no header/config/marker edits retained, verify +0/-0 and unit order0. Keep NonMatching. Evidence in primary build/evidence/eggplane-20261102: scripts, per-source variants/sweeps/scores/diffs and result JSON. Next work needs new original copy/inline evidence, not these scalar captures or assignment helpers.
