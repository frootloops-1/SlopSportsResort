# Permuter found int new_var2 = 1 hoisted constant + do{...}while(0!=0) wrapper for fn_801F8750; declare-then-assign name for fn_801F89DC

- status: works
- tags: permuter,regalloc,sched
- scope: Pack/RPSports/RPSportsCommon

symptom: fn_801F8750/fn_801F89DC 99.38%: sched of li 1 and name = base+offset vs stores
cause: hoisted shared constant 1 reused across setMessage args, anm alias, deferred name assignment
fix: see source: int new_var2 = 1 reused for text index/args/f6; SpAnmView* new_var = anm; do{const char* name=base+0x28; ...}while(0!=0); and const char* name; ... name = base+0x45 after the f5 store
