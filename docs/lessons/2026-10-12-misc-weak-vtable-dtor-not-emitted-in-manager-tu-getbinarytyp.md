# Misc weak vtable/dtor not emitted in Manager TU: GetBinaryType in other TU is key function

- status: open
- tags: key-function,vtable,weak,RPGrpModelMisc,split
- scope: RPGrpModelMisc/RPGrpModelManager
- source: sonnet worker 2026-10-12

symptom: GetVersion/__dt__/Set,GetBinaryInner/__vt__14RPGrpModelMisc (weak in orig Manager range) not emitted by our Manager TU
cause: MWCC treats out-of-line GetBinaryType (Misc.cpp) as key function; vtable lives in Misc TU
fix: Tried: declaration order, dtor first, defining GetBinaryType in Manager cpp (global vtable, wrong order, duplicate), inline GetBinaryType (breaks Misc.cpp). Dropping virtual on overrides errors under -w err. Open.
