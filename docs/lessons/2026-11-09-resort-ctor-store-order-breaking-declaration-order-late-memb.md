# resort: ctor store order breaking declaration order = late members assigned in body

- status: works
- tags: resort,rp,data

symptom: ctor stores out of order
cause: members set in body, not init list
fix: move them from the init list into the body (RPSysScene 0x5C/0x60/0x6C)
