# early returns in TRKPPCAccessFPRegister

- status: fails
- tags: metrotrk,targimpl
- scope: MetroTRK/debugger/Processor/targimpl.c
- source: subagent

symptom: .text drops 99.82 to 98.13
cause: n/a
fix: dead end; static inline on helpers also no change
