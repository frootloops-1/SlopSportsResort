# KPADInit: KPADSetBtnRepeat(i,0,0) inline call instead of hand stores regresses

- status: fails
- tags: KPAD,inline
- scope: revolution/KPAD/KPAD

symptom: sibling SDK revision calls KPADSetBtnRepeat inline in KPADInit
cause: inlined call recomputes kp as a separate induction pointer (mr r25,r26) and an extra saved reg
fix: keep hand-written btn_repeat stores (99.5 -> 96.8 with the call)
