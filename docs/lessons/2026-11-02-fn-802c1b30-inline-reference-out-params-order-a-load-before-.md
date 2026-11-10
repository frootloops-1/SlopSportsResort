# fn_802C1B30: inline reference out-params order a load before caller locals

- status: works
- tags: schedule,inline,regalloc,RPGol,MATCH-PENDING
- scope: Pack/RPSports/RPGolScene/RPGol_802c16a4

symptom: one shot-field load scheduled after three other field loads; making it a named local fixes schedule but swaps it with self (r23/r24)
cause: the value must stay an inline by-value param (coloured last) yet be emitted before the caller locals' loads
fix: inline takes the 0x114 count by value and assigns caller locals target/t118/pos through reference params (99.9 -> 100), marked MATCH-PENDING (R17), ledger row 76
