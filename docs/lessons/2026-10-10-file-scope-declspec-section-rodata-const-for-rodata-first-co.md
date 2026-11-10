# file-scope declspec(section .rodata) const for rodata-first constant; reverse-order file for -inline deferred

- status: works
- tags: metrotrk,dolphin_trk,glue
- scope: MetroTRK/debugger/Os/dolphin
- source: subagent decomp-standard, verified

symptom: local static const u32 lands in sdata2; pool/text order wrong
cause: -sdata2 default threshold; inline deferred emits reverse order
fix: file-scope __declspec(section ".rodata") static const; write file in reverse address order; separate empty C function reproduces 4-byte blr gap; mtspr 27 for srr1
