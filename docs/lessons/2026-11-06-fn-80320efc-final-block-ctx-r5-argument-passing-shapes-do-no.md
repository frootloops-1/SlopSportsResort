# fn_80320EFC final-block ctx r5: argument-passing shapes do not help

- status: fails
- tags: RPBow_80320EFC,fn_80320EFC,gpr
- scope: fn_80320EFC

symptom: ctx r4 vs retail r5; retail loads vA0.x (0xa0) first, ours .y first
cause: unknown; Set(x,y) by value evaluates args right to left (y first), and retail loads x first
fix: none. Dead: BowMakeVec2 by-value return (131), inline Set helpers with ctx or the vec as arg0/argN (5-7), inner if moved into an inline taking ctx (5-7)
