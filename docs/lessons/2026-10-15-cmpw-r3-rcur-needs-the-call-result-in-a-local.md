# cmpw r3,rCur needs the call result in a local

- status: works
- tags: cmpw,operand-order,call
- scope: RPTns
- source: RPTns_80235cd0

symptom: cmpw rCur,r3 for fn()==cur
cause: MWCC puts the variable first either way
fix: int sd = fn(e); if (sd == cur)
