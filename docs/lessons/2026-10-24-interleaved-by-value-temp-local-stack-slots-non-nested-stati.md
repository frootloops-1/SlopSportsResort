# Interleaved by-value temp / local stack slots: non-nested static inline helper holding local + full body

- status: works
- tags: stack-layout,inline,gxcolor
- scope: RPUtility
- source: claude

symptom: four by-value GXColor local+temp pairs: all locals above all temps (fn_801C3D40), or local below copy temp (fn_801FFEE0)
cause: inlined helper boundary decides slot allocation order
fix: one non-nested static inline helper that holds the local GXColor AND the call taking it by value, called N times; calling a nested inline from the helper does not work. Writing helper bodies directly in the caller also fixes swapped VEC3 operator temps (fn_80339E5C)
