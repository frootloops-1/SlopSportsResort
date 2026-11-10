# Global-pointer local that should get the lowest callee-saved reg: T* const, declared last

- status: works
- tags: regalloc,const,declaration-order,callee-saved
- scope: RPTns_80238a18
- source: sonnet worker 2026-10-14

symptom: callee-saved locals allocated in reverse (root r31 vs target r28/r29); declaration permutations fail
cause: MWCC treats a const-qualified pointer local differently in coloring order
fix: T* const root = global; declared after the other locals; others then follow declaration order (fn_80238E78/FB4 99.2 -> 100)
