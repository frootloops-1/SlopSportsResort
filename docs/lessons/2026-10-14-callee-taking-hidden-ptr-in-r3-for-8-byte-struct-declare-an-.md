# Callee taking hidden ptr in r3 for 8-byte struct: declare an out-param

- status: works
- tags: abi,struct-return
- scope: RPGol_802b7448
- source: fn_802B7458

symptom: 8-byte struct return used r3/r4 in ours
cause: MWCC returns 8-byte structs in r3/r4
fix: declare fn_X(GolV2* out, ...) instead of returning GolV2
