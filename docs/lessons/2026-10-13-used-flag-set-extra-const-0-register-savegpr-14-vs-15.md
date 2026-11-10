# Used-flag set: extra const-0 register (savegpr_14 vs _15)

- status: open
- tags: mwcc,regalloc,fn_802B9688
- source: RPGol_802b90b4

symptom: orig rematerializes li r0,k before each cmpwi used_k; ours holds 0 in r14
cause: unknown
fix: bool used[8]+inner loop 59.8 (stack); 8 bool locals else-if chain 75.5 best so far
