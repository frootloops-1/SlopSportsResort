# fn_8025404C tail: li 8 in r4 vs r0 (addi vtable+0x24 hoisted), forecast lever 9 flat

- status: fails
- tags: forecast,regalloc,scheduling,inline,parked
- scope: RPBsb_80252e7c/fn_8025404C
- source: forecast-regalloc

symptom: 2nd InitSoundBase expansion: target li r0,8 reused then addi r0,r3,0x24 after stw 0x44; ours li r4,8 with addi r0 hoisted (8 lines, 98.7)
cause: prepass schedule makes the 8 and vtable+0x24 temps interfere; not a declaration-order issue
fix: dead ends: (u8*)lbl+0x24, local void** vt, chained float stores, named s32 n=8 in InitSoundBase (lever 9)
