# TRK -inline deferred reverses fn order: jump table relocs

- status: works
- tags: trk,metrotrk,msghndlr,jumptable,order,inline-deferred
- scope: MetroTRK

symptom: fn asm identical (asm_diff) but 99.9%: jumptable reloc points to wrong table (@205 vs jumptable_..64); bss globals in reverse order
cause: GC/2.7 -inline deferred emits functions (and their switch tables) in reverse source order
fix: write the functions in reverse address order; declare file globals in reverse too (and non-static if orig global). msghndlr Read/WriteMemory -> 100
