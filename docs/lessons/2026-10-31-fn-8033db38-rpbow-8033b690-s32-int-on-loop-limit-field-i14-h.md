# fn_8033DB38 (RPBow_8033B690): s32 -> int on loop-limit field i14 has no effect (96.0 unchanged)

- status: fails
- tags: rpbow,8033db38,s32,int,loop,nogain
- source: orchestrator 2026-10-31

symptom: checked after the 8034C230 s32(long)-vs-int fold fix: i14 is s32 limit of int counters in the pair loops
cause: no effect here; this function's residue is colouring/pre-RA schedule (see earlier 8033DB38 lessons)
fix: dead: int i14; unchanged 8/9 fns, .text 99.35. Cheap check, not worth repeating.
