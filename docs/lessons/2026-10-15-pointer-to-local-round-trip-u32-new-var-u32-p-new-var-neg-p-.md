# Pointer-to-local round trip (u32 new_var; u32* p=&new_var; neg=*p) permuter pattern

- status: open
- tags: permuter,stack,branch
- scope: Pack/RPSports

symptom: fn_801FACAC 99.72%
cause: permuter-found new_var/new_var2 pattern
fix: 99.97% after port; one BRANCH-DEST left (bne after srwi.); permuter stand-in said 0 but the real build differs by one branch dest
