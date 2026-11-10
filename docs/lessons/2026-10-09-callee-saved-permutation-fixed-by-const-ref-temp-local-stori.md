# Callee-saved permutation fixed by const-ref temp + local-storing getter (fn_8028F0E8)

- status: works
- tags: RPGolCameraManager,regalloc

symptom: m/bpos adjacent, no decl order helps; 99.3%
cause: temp/getter-local rank differently in MWCC GPR priority
fix: player via inline getter that stores into local then returns; GolPin* const& pin = getGolPin(); (compiler temp ranks between bpos and m)
