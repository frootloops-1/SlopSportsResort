# Jump-table fn stuck at 99.9% identical code: .data offset

- status: works
- tags: jumptable,data,RPGolFieldManager,reorder

symptom: identical code but 99.8-99.95%
cause: jump table at different .data offset
fix: define preceding .data objects (lbl_803C77F8[3]); MWCC emits funcs in reverse definition order; const T& bound to struct-returning inline fixes &local arg order; bool field gives srwi
