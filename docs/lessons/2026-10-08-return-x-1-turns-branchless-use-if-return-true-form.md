# return x==1 turns branchless; use if-return-true form

- status: works
- tags: mwcc,branchless,bool

symptom: original cmpwi/bne/li/blr, ours cntlzw/srwi
cause: single return of a comparison is compiled branchless
fix: if (cond) return true; return false; and OR chains as if (a||b) return true; return false;
