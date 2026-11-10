# Thunk pitfalls: unused param, vtable store, dont_inline

- status: works
- tags: thunk,vtable,inline,RPGolFieldManager

symptom: void(void*) thunk errors under -w err; vtable store loads value; callee inlined
cause: unused param; 'extern void* lbl' loads value; dont_inline does not block same-TU callee inlining (fn_8029126C dead end)
fix: drop the param; use 'extern char lbl[]' for address
