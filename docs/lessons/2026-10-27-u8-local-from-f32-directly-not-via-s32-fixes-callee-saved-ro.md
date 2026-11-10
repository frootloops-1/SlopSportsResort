# u8 local from f32 directly, not via s32, fixes callee-saved rotation

- status: works
- tags: gpr,cast,callee-saved
- scope: RPUtlDohGraphSun
- source: claude/rputl-doh-1027

symptom: r22/r23/r24 rotation between params and short temps across a long loop body
cause: u8 x = (u8)(s32)(f) vs u8 x = f changes the hoisted temp's priority
fix: u8 flareAlpha = 255.0f * alpha; (fn_801C1DCC 98.5 -> 99.9)
