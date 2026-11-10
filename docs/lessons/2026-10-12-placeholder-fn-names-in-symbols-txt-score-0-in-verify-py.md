# Placeholder fn_ names in symbols.txt score 0 in verify.py

- status: works
- tags: symbols,verify
- scope: RPKernel
- source: RPSysTagProcessor/SystemWinMgr 2026-10-12

symptom: compiled mangled symbol never pairs
cause: symbols.txt still has fn_XXXXXXXX
fix: rename to the compiled mangled name (and fix extern C callers)
