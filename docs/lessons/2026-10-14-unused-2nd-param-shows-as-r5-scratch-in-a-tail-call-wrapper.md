# Unused 2nd param shows as r5 scratch in a tail-call wrapper

- status: works
- tags: params,regalloc,tailcall
- scope: RPTns_8022ef18
- source: sonnet worker 2026-10-14

symptom: function uses r5 as scratch instead of r4
cause: it has an unused second parameter
fix: declare it and pass it through to the callee (avoids error 10182)
