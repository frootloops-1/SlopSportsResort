# RPSysPauseMenu has no vtable; ~X(){} gives deleting-dtor shape

- status: works
- tags: rpsyspausemenu,vtable,dtor
- scope: Pack/RPKernel/RPSysPauseMenu

symptom: draw 26.8%, dtor/ctor not scored
cause: class wrongly declared virtual; original dtor stores no vtable
fix: drop virtual (size 0x88); type mUtlCursor as RPUtlLytFrameCursor stub w/ virtual draw at vtable +0x14; rename fn_801A0BE0/C20 to __dt__/__ct__ in symbols.txt so verify pairs them
