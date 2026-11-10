# fn_8021013C SpVec3f read/dead stack pair: out-of-line or auto-inlined ctor/set, named CurPos, inline-ctor without set do not move the read slot

- status: fails
- tags: stack,temps,rpsports,8020f530
- source: sp8020f-1104

symptom: read copies at frame bottom (0x08/0x10) instead of next to the dead copies (0x28/0x38)
cause: set() param temps created in a later inlining pass than the helper's temps
fix: open; try a by-value-param shape where the call result temp is created in the same expansion
