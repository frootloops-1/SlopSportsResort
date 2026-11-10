# resort: @NN@ thunk branching outside the unit = weak implicit dtor linked earlier

- status: works
- tags: resort,rp,data

symptom: thunk target unnamed, out of unit
cause: first weak copy of dtor/inline virtuals lives in an earlier unit
fix: rename that address to __dt__... scope:weak; same for inline virtuals in the vtable (RPSysScene 0x801CF5D8..)
