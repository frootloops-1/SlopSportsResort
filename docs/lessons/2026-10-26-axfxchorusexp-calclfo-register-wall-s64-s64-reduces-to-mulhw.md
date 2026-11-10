# AXFXChorusExp __CalcLFO: register wall, s64*s64 reduces to mulhw

- status: fails
- tags: axfx,s64,mulhw,register,calclfo
- scope: src/revolution/AXFX/AXFXChorusExp.c
- source: axfx-chorus-1026

symptom: __CalcLFO 30 lines, register choices only (a in r31 vs r11, high sum in fresh reg vs mulhwu reg)
cause: CW reduces s64*s64 of sign-extended s32 to a single mulhw through locals/inline helpers; only a (u64) cast gives the full mulhwu+cross-term form
fix: 30+ spellings (cast placement, operand/statement order, decl scope, table ptr, b local) and 9 min permuter stay at 30 lines; parked at Opus ceiling
