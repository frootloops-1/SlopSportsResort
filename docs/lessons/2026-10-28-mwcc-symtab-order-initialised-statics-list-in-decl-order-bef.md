# MWCC symtab order: initialised statics list in decl order before functions

- status: works
- tags: symtab,sbss,static,order,sdk-objects
- scope: all units
- source: NdevExi2A.a DebuggerDriver.o

symptom: original .o symtab lists sbss statics in ascending address order ahead of the static functions; ours lists them by first use
cause: uninitialised statics are emitted lazily (first use, reverse decl layout); '= 0' statics are emitted at definition in decl order and laid out in decl order (still .sbss)
fix: declare with '= NULL/0' in ascending address order; code unchanged
