# Local TextWriterBase copy emits stray weak CharWriter dtors

- status: works
- tags: weak,textwriter
- scope: RPKernel
- source: RPSysTagProcessor/SystemWinMgr 2026-10-12

symptom: extra weak __dt__ in text
cause: inline copy ctor
fix: harmless: linker strips; confirm via DOL check
