# inline helper local const table is shared across callers

- status: works
- tags: rodata,inline,aggregate,rpbsb
- source: RPBsb_8028aef0 2026-10-16

symptom: extra 32B @NNN rodata table appears
cause: each function-local const aggregate gets its own table; one inside an inline helper is pooled once
fix: call the same inline helper from all users (bool param for set/clear), index param s32 not u32
