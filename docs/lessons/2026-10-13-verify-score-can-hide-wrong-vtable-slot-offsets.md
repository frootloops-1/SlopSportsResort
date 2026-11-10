# verify score can hide wrong vtable slot offsets

- status: works
- tags: objdiff,vtable,verify
- source: RPGol_802b90b4

symptom: fn scored 100 in verify.py but every lwz r12,N(r12) slot offset was +8
cause: objdiff score did not penalise the slot immediates here
fix: after matching a fn with virtual calls, confirm with tools/asm_diff.py <unit> <fn>
