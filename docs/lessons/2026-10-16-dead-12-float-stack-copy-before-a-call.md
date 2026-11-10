# dead 12-float stack copy before a call

- status: open
- tags: stack,dead-locals,frame,rpbsb
- source: RPBsb_8027d3ec 2026-10-16

symptom: stfs to 8..0x34(r1), only r3/f1 passed (fn_8027D9BC)
cause: dead locals, not args; MWCC scatters dead slots (0xA0 frame vs 0x40)
fix: best 95.7: four ctor-built dead Vec locals then call; by-value/variadic/13-float args all fail; volatile array 31%
