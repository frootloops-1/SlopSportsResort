# Pointer-to-local trick: T* new_var; new_var=&x; use *new_var fixes reg/ordering (permuter)

- status: works
- tags: permuter,regalloc,stack
- scope: Pack/RPSports/RPTnsScene

symptom: fn_8021F13C, fn_8021EA20 (u32 id passed to virtual), fn_80211480 (AnmView* a): 98.9-99.1% register/order diffs
cause: taking the address of a local via a throwaway pointer changes allocation; permuter pass names it new_var
fix: declare T* new_var; assign &local before first use and read through *new_var (fn_80211480: (*(new_var=&a))->f5=zero; (*new_var)->f6=1) -> exact
