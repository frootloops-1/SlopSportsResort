# msg local r27 vs r30 after three name loops (fn_8024720C, fn_80247740)

- status: open
- tags: regalloc,callee-saved,loops
- scope: RPTns_80246eec,RPTns_80247450
- source: claude 2026-10-14

symptom: orig coalesces strbase/name temps/msg into r30; ours msg gets r27 (first loop counter reg)
cause: unknown coloring order
fix: failed: const msg, decl before acc, top-level uninit, block scope, split counters, holder temp, reload each call
