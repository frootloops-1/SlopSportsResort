# Small later fn auto-inlined into callers under -inline deferred

- status: works
- tags: inline,deferred
- scope: RPKernel
- source: RPSysTagProcessor/SystemWinMgr 2026-10-12

symptom: earlier caller drops to 0 after defining a small later function
cause: -inline deferred auto-inlines later-defined small fns
fix: wrap definition in #pragma auto_inline off / reset
