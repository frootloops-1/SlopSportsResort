# LoadScnLightInner: merge-into-existing-branch loop shapes do not give the offset counter

- status: fails
- tags: regalloc,LightManager,induction,IRO,loop,egg
- scope: egg/gfxe/eggLightManager

symptom: loop 1 needs IRO's offset counter without extra code
cause: a wrapping if (flags/lightNum!=0) keeps its compare and IRO still rotates to the pointer form; loop-condition spellings do not stop the rotation
fix: failed: if (m_flags & UseScnLightSet) wrap (20 lines), if (lightNum != 0) wrap (18), while loop (17), shared u32 i + set copy (15), lightNum > i (17), i != lightNum (19), u16 i (38)
