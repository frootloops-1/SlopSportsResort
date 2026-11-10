# RPSports_801f9150: literals, defer_codegen off, descending order, inline helpers; unit holds two TUs

- status: works
- tags: string-pool,regalloc,inline-helper,tu-split,RPSports_801f9150
- scope: RPSports_801f9150

symptom: fn_801FA6D8 90.7, fn_801FA014 99.95, .rodata 68, .sbss 0
cause: string blob extern + undefined tables; loop counter coloured behind strength-reduced pointers; unit actually spans two TUs (text 0x801F9150-0x801F9534 looks separate: 8-byte chunk ends in rodata/data/sbss)
fix: Literals + tables at file end + defer_codegen off + reorder_fn; static inline wrapper around the text-box loop colours the counter first (R17 102-104). fn_801F9A00 98.0: SetVisible(true) flag byte r5 vs r0 unresolved. Split decision pending (merge into RPSports_801f8750 or new unit).
