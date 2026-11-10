# resort: functions emitted after __sinit (MI thunks, array-element ctor) belong to the unit before

- status: works
- tags: resort,splits,sinit
- scope: resort
- source: bowling-splits

symptom: subi r3,r3,N; b thunks and a __construct_array element ctor sit after a unit's __sinit
cause: '__sinit is always last' has exceptions: MI thunks and ctors only referenced by the sinit's __construct_array
fix: extend the unit's .text end past __sinit to include them (RPBow_8031EFE4, RPBow_80323790)
