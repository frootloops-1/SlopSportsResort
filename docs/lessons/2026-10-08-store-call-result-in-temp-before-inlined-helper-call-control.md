# Store call result in temp before inlined helper call / controller mgr load order

- status: works
- tags: regalloc,scheduling

symptom: zero-extension or CoreControllerMgr instance load scheduled before the call instead of after
cause: nested call as argument
fix: put fn_801DFFE0 result and getPlayerCursorChannel result in temps (fn_801E12E8)
