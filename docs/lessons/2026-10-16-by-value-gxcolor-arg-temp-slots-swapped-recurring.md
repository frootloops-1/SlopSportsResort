# by-value GXColor arg temp slots swapped (recurring)

- status: open
- tags: stack,gxcolor,byvalue,rpbsb
- source: RPBsb_8027c2f0 2026-10-16

symptom: two by-value color args: orig temps 0xC then 0x10, ours 0x10 then 0xC (fn_8027CBD8, fn_8028B610 99.7-99.9)
cause: unknown; arg-temp allocation order
fix: tried: declaration order, global direct, copies, hoisting, no scr local - all 99.9; untried: permuter
