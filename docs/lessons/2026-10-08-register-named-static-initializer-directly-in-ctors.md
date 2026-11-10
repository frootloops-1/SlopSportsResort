# Register named static initializer directly in .ctors

- status: works
- tags: ctor,static-initializer,mwcc,duplicate-emission
- scope: Pack/RPUtility/RPUtlObject/fn_801BFE74
- source: docs/tasks/RPUtlObject.md

symptom: Naming the body while retaining a C++ static initializer improves pairing but emits a duplicate __sinit body and grows source text by 52 bytes.
cause: The compiler emits both the explicit function and the automatically registered initializer; fuzzy section metrics do not reject the source-side duplicate.
fix: Use the existing CodeWarrior __declspec(section ".ctors") static function-pointer registration; independently check ctor relocation, source sizes and emitted helpers. Constructor attribute was rejected here because .ctors scored 0%.
