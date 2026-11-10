# One extra inline level shifts FPR vreg numbering

- status: works
- tags: RPBox,asm,R17
- scope: Pack/RPSports/RPBoxScene/RPBox_802cf93c

symptom: FPR colour residue (fn_802D1BD8)
cause: FPR colour residue (fn_802D1BD8)
fix: wrap one inline helper call in a one-level static inline wrapper; two levels overshoot
