# MWCC speculates the constant arm of ?: even via a non-initialiser local or bool condition variable

- status: fails
- tags: ternary,select,rpsports,80211b60
- source: sp8020f-1104

symptom: fn_802131C8 li r8,2; bne; mr r8,r9 vs retail beq; li r8,2
cause: constant (or propagated-constant) arm always materialised before the branch; tried two=2 assignment, bool normal = fC==0, swapped arms, casts, kind types, hoisted arg locals (95.1)
fix: open
