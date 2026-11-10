# Unexplained r4/f1 before a call: check callee's real params

- status: works
- tags: abi
- scope: RPGol_802b8568
- source: fn_802B8D98

symptom: 84% scheduling mismatch
cause: callee takes (void*, s32, float)
fix: pass the hidden args; compute float expr first
