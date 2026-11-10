# Dead stfs fN,8(r1) before call = 9th float arg on stack

- status: works
- tags: args,float,stack
- scope: RPTns_8022863c
- source: opus worker 2026-10-14

symptom: dead-looking stfs f8,8(r1) before a call passing f1..f8
cause: callee takes a 9th float passed on the stack
fix: pass all 9 floats (fn_801BE810 in RPTns_8022863c)
