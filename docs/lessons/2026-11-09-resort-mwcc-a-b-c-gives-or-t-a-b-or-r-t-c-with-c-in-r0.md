# resort MWCC: a | (b | c) gives `or t,a,b; or r,t,c` with c in r0

- status: works
- tags: resort,mwcc,or,register

symptom: plain a|b|c swaps registers
cause: MWCC evaluates a|b|c as c | (a|b)
fix: Write a | (b | c), or a |= b; r = a | c
