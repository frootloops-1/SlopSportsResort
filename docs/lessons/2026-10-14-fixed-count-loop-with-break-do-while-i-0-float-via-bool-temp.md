# Fixed-count loop with break: do-while --i>=0; float > via bool temp for mfcr

- status: works
- tags: loops,ctr,mfcr
- scope: RPTns_8022e3f8

symptom: mtctr/bdnz vs orig subic./bge; ble vs mfcr+extrwi.
cause: for loops become ctr loops; direct if(a>b) branches
fix: do { } while (--i >= 0); bool gt = a > b; if (gt)
