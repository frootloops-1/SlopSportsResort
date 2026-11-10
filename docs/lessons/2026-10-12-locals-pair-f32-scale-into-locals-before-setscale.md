# Locals pair f32 scale into locals before SetScale

- status: works
- tags: float,regalloc
- scope: RPKernel
- source: RPSysTagProcessor/SystemWinMgr 2026-10-12

symptom: f1/f2 swapped for percent/100.0f arguments
cause: inline arg evaluation order
fix: f32 a=p/100.0f; f32 b=p/100.0f; SetScale(a,b)
