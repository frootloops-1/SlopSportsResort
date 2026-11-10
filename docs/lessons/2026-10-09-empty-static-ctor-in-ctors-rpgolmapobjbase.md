# Empty static ctor in .ctors (RPGolMapObjBase)

- status: works
- tags: golf,ctors,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: haiku

symptom: unit .ctors has one entry pointing at blr function
cause: empty static initializer
fix: extern C void fn(){}; __declspec(section ".ctors") static void (*x)() = fn;
