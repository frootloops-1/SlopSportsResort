# Field-typed stores instead of byte-array casts free scheduler hoisting (b340 F120)

- status: works
- tags: schedule,stores,alias,b340
- scope: RPSportsCommon/RPSports_8020b340
- source: claude/b340-1104b 560151bb0

symptom: mode/const 1 wrong regs; f198c load not hoisted
cause: (f32*)u8-array cast stores alias the later s32 field load, blocking hoist
fix: Write float clears as typed field stores (a[i].x...), retail store order, read mode just before the if. F120 99.2->100
