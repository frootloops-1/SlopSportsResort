# Inline bool helper that rereads the global but not the field

- status: works
- tags: inline,regalloc,bool,reload
- scope: RPGolMain

symptom: fn_8028E2EC 97% (second state test needs lwz 0x94(r5) reload, li r3 result)
cause: second compare read through a fresh global pointer
fix: IsStateB: v->state==3 || ((const GolStateView*)lbl_804BF8C4)->state==6; MWCC merges the global load but not the field load
