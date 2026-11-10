# Vtables are emitted in the TU of the key virtual function

- status: works
- tags: vtable,data,split,key-function
- scope: RPGol_802c16a4
- source: claude/rpgolscene-unsplit

symptom: .data vtables {0,0,dtor in TU X, method in TU Y} sit inside TU Y's .data range though ctors live elsewhere
cause: vtable goes with the first non-inline virtual (key function)
fix: assign the vtable to the TU defining the non-dtor slot functions when choosing .data split ranges
