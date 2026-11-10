# InitMetroTRKCommTable string pool hoist

- status: open
- tags: metrotrk,glue
- scope: MetroTRK/debugger/Os/dolphin/dolphin_trk_glue.c
- source: subagent decomp-standard

symptom: orig hoists pool base to r29 and 4-aligns strings; ours repacks
cause: unknown; Wii/1.x compilers hoist but layout wrong (same as TRKDoSetOption)
fix: untested: other compiler version for MetroTRK
