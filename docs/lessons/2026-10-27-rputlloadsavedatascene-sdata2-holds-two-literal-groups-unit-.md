# RPUtlLoadSaveDataScene .sdata2 holds two literal groups: unit is two TUs

- status: open
- tags: RPUtlLoadSaveDataScene,sdata2,split,duplicate-literal
- source: claude/rputl-lsds-1027

symptom: all 61 fns exact but .sdata2 75%, DOL 32 bytes short on flip
cause: 0,1,-1 appear twice (0x804C1C70 group for fn_801CB58C..fn_801CBA0C, 0x804C1C88 group for fn_801CBE74); one TU pools them
fix: split unit: TU A .text 0x801CB500-0x801CBB98 /.data ..0x803C1BA8/.sdata2 ..0x804C1C88; TU B the rest (boundary in 0x801CBB98..0x801CBE74 undetermined)
