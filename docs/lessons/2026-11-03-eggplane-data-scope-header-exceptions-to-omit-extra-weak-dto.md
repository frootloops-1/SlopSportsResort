# eggPlane data: scope header exceptions to omit extra weak-dtor records (R17)

- status: works
- tags: egg,Plane3f,extab,extabindex,exceptions,weak,destructor,R17
- scope: egg/geom/eggPlane
- source: 2026-11-03; build/evidence/eggplane-data-20261103/

symptom: Both functions and linked DOL matched, but raw extab/extabindex scored 66.66667%: source 16/24 bytes versus target 8/12, from an extra weak Vector3f destructor.
cause: Exception metadata generation is attached to inline definitions when the headers are parsed. Disabling exceptions only around later out-of-line helper definitions leaves the destructor metadata unchanged; deferred header codegen also fails.
fix: Marked R17 scope: #pragma exceptions off before #include <egg/geom.h>, then #pragma exceptions reset immediately after. Target extab/extabindex now both 100%, exact 8/12 bytes, and both functions remain exact on all six GC builds. Full DOL remains 0 differing bytes with only three known address collisions, so this weak destructor does not replace the selected linked definition. Its unused 64-byte body still exists but is linker-discarded. Original header exception settings remain unknown; no shared headers or config flags changed.
