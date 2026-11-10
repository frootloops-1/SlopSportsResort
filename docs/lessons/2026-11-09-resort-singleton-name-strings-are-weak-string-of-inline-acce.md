# resort: singleton name strings are weak @STRING@ of inline accessors

- status: works
- tags: resort,rp,data

symptom: flip fails on .data order: name string after vtables
cause: string literal inside an inline accessor emits a weak @STRING@ object; linker keeps one copy
fix: pass the literal in the accessor (RPSysUnkSingletons.h) and rename lbl to @STRING@Get<Name>__Fv; RPSysSystem flipped
