# resort: callee ignoring r5 while a caller loads a byte into r5 = unused bool param

- status: works
- tags: resort,rp,data

symptom: caller lbz r5 before call
cause: parameter unused in body
fix: rename to the 2-param mangling (destroyHeap__11RPSysSystemFPQ23EGG4Heapb)
