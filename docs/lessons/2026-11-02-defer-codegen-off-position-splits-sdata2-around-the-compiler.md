# defer_codegen off position splits .sdata2 around the compiler magic double

- status: works
- tags: sdata2,defer_codegen,magic-double,vtable,jumptable
- scope: RPGolFieldManager
- source: claude/golfield-data-1102

symptom: explicit extern const f32 table defined at file end puts the compiler-made u32->f32 magic double @N first (offset 0) instead of between lbl_804C3F2C and lbl_804C3F38; DOL shifts sda21 offsets by 8
cause: file-scope consts are emitted at parse; the magic double is created at codegen (flush). #pragma defer_codegen off flushes after the first definition that follows it, not at the pragma
fix: define constants up to the double's slot BEFORE the pragma, then the pragma, then a harmless def (sbss) + vtables, then the remaining constants. Jump tables then precede the vtables too. Functions stay exact (no const folding because defs come after all functions parse)
