# MSL alloc: helpers are inlined; define static inline before the caller

- status: works
- tags: msl,inline,alloc,permuter
- scope: MSL_C ports
- source: claude/msl-text alloc.c 2026-10-09

symptom: Block_link 58% plus stray standalone helper functions; free has r30/r31 swap
cause: original has SubBlock_merge_prev, __unlink, deallocate_from_var_pools, __pool_free inlined (no symbols); a later definition is never inlined
fix: static inline helpers defined before callers; in free, 'pool = get_malloc_pool(); __pool_free((0, pool), ptr);' (comma operator) found by tools/permute.py setup MSL/alloc free (unit needs MSL/ prefix)
