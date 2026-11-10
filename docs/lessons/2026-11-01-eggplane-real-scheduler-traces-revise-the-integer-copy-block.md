# eggPlane real scheduler traces revise the integer-copy blocker; alias, base layout and subtraction operators give no gain

- status: fails
- tags: egg,plane,scheduler,alias,inheritance,operator,compiler
- scope: egg/geom/eggPlane
- source: codex-eggplane-1101, base 0224b99a8

symptom: project 73.17073%, helper 100%; unit remains NonMatching.
cause: Real GC/3.0a5.2 traces show dot(rVec) DOES hoist float loads across the lwz/stw return copy; the older blanket no-early-load explanation is too strong. The pre-RA schedule yields different lifetimes. An exact reduced two-base-layer type reproduces both 73.17073% dot(work) and 66.80488% dot(rVec); flattening the POD base changes scalarization to 53.26829%. Const/plain scalar accesses, POD/union/base-dtor variants, processor models, and copy-then-subtract operator variants do not improve it. Six GC builds agree for every source probe.
fix: No source/config/header edits retained. Next: instrument the native GC3 scheduler dependency/priority decisions for the exact reduced reproducer, especially v.y vs normal.y and early normal.x/normal.z loads; compare the resulting FPR interference graph with retail. Do not repeat these source probes or infer an absolute integer-copy barrier. Evidence: /private/tmp/ogws-eggplane-1101/build/evidence/eggplane-1101/{debug-baseline,debug-input,*-results.json,*-versions.log,probe.py,type-probes.py,operator-probes.py}; current object .text 78.43% size-weighted. Configured main.dol DOL 0 excludes this NonMatching unit and is not a Plane closure.
