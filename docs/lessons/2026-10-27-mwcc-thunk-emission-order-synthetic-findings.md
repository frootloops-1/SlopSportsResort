# MWCC thunk emission order synthetic findings

- status: works
- tags: thunk,vtable,template
- scope: egg
- source: drawpathbase-1027

symptom: need to predict @N@ thunk emission order
cause: non-template secondary base: emitted in reverse slot order (dtor slot included where declared); template base (IBinary<T>): forward slot order; groups across bases forward; a vtable for another class in the TU (generated earlier) pre-creates shared thunks
fix: no change from: explicit dtor declared/defined anywhere, delete/virtual-call uses, declared-but-not-instantiated derived class (no vtable emitted). Test harness: compile small .cpp with the unit's mwcc flags, then dtk elf disasm
