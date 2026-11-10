# fn_80339E5C count/const1/offset triple swap: BowWallContactCount inline and dropping sample local regress

- status: fails
- tags: regalloc,forecast,fn_80339E5C,RPBow
- scope: fn_80339E5C

symptom: r23 count / r30 const1 / r31 offset vs target r30/r31/r23
cause: three-way colouring order; diagnoser lever 1 (declare up front) not applicable as values are expression temps
fix: dead ends: use existing unused inline BowWallContactCount(m) as loop limit (99.9->99.6); remove 'int sample=m' local (->62 diff lines). Parked.
