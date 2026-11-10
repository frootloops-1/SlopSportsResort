# call arguments evaluated right to left

- status: works
- tags: regalloc,args,rpbsb
- source: RPBsb_8027c2f0 2026-10-16

symptom: msg register r29 vs r30
cause: MWCC evaluates fn(a(), b()) b first
fix: keep the nested call inline in the argument list instead of a named local
