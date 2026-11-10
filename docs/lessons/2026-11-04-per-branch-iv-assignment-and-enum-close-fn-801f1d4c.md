# Per-branch IV assignment and enum ?: close fn_801F1D4C

- status: works
- tags: iv,strength-reduction,register,enum,ternary
- scope: RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104b 81e690091

symptom: base-IV vs value-walk register swap; which temp on r5 instead of r0
cause: Where base=j*3 is assigned orders strength-reduction IV creation; int ?: goes branchless, enum ?: keeps branch and numbers which as an early temp
fix: Assign base=j*3 inside each branch after the value read; which = i==0 ? Enum_2 : Enum_1
