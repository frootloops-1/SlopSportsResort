# fn_8028E2EC: state-test inline helper shapes cap at 97%

- status: fails
- tags: inline,regalloc,bool
- scope: RPGolMain

symptom: orig keeps singleton in r5 and reloads 0x94(r5) for ==6 test, li r3 for bool
cause: unknown
fix: tried ==chains, local int, bool r=..., ternary: 96.8-97.0%
