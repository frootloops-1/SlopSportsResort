# Tail-call stub with mr r7,r3: callee takes more args

- status: works
- tags: abi,stub
- scope: RPGol_802adb7c
- source: fn_802AE064

symptom: temp reg r5 vs r7
cause: stub forwards r5/r6
fix: use callee's real signature and forward args
