# resort: callers through extern C fn_ names block renames

- status: works
- tags: resort,symbols,rename

symptom: renaming a function whose C++ callers use extern "C" fn_<addr> breaks the link
cause: Placeholder extern C declarations bind to the fn_ name
fix: grep src for fn_<addr> before renaming; switch the callers to the real method in the same change (RPSysSceneMgr softReset/returnToMenu/shutdownSystem/CreateInstance: +4 exact)
