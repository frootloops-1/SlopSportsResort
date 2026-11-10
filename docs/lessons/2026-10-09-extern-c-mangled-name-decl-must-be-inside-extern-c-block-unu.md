# extern C mangled-name decl must be inside extern C block; unused named param is error 10182

- status: works
- tags: golf,extern-c,warnings,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: sonnet

symptom: decl outside extern C gets re-mangled; unused param fails -w err
cause: CW C++ linkage + warnings as errors
fix: wrap decl in extern "C"; leave unused params unnamed
