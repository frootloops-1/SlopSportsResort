# Inline arg order/range-first helper fixes VEC3Scale + weight FP colors

- status: works
- tags: mwcc,regalloc,fp,inline,golball
- scope: RPGolMapObjBall fn_80298A44
- source: claude/golball-c-1107 1e3aa320d

symptom: VEC3Scale(side) followed by a response-weight/clamp/VEC3Lerp block: FP colors of scale constant, range and zero differ
cause: The coloring order follows inline-expansion vreg order; computing range before VEC3Scale inside one inline gives zero f0, scale f1, range f3
fix: static inline ScaleBlend(out, rot, scale, speed) { f32 range = C58; range -= C30; VEC3Scale(rot, rot, scale); weight/clamp/lerp } -> fn_80298A44 100% (R17 row 222). Also: chained a = b = 0 stores b first
