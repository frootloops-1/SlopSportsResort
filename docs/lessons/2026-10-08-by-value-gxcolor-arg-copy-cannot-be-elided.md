# By-value GXColor arg copy cannot be elided

- status: fails
- tags: mwcc,gxcolor,stackcopy

symptom: original passes &field directly; we emit 4-byte stack copy (frame 0x40 vs 0x30)
cause: unknown
fix: tried GXColor/ut::Color field, const by-value decl, inline wrapper, inline returning by value: all copy
