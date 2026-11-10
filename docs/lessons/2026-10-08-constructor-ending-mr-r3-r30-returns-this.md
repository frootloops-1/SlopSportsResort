# Constructor ending mr r3,r30 returns this

- status: works
- tags: mwcc,ctor

symptom: ctor 97.9%
cause: missing return of this
fix: give the extern C ctor a Self* return type
