# mwcc_dbg on one of several ctors: scratch copy of mwcc_debugger.py with 'name#N' (Nth function with that linkname)

- status: works
- tags: tooling,mwcc_dbg,ctor
- scope: Pack
- source: claude/sp801f1-1104

symptom: mwcc_dbg.sh matches unqualified names; every ctor is '__ct', first match wins
cause: debugger compares func.linkname to FUNCTION_NAME once
fix: copy ~/Downloads/ogws-tools/mwcc-debugger/mwcc_debugger.py to scratch, count matches of the name before '#', break at N; run with MWCC_DEBUGGER=<copy> tools/mwcc_dbg.sh <unit> '__ct#5' <out> (functions are visited in address order)
