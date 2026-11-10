# Tail-called callee arg keeps caller temp register (fn_8028EAE0)

- status: works
- tags: RPGolCameraManager,regalloc,tailcall

symptom: temp in r4 instead of orig r5 for a 7-insn compare+tail call
cause: callee fn_802C441C takes 2nd arg (stw r4,0x78(r3)); the caller's r4 param stays live
fix: declare callee (GolCam*, int) and pass caller's 2nd param through
