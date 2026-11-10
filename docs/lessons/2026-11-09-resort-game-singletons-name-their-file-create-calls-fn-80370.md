# resort: game singletons name their file: create calls fn_80370BD8(inst==NULL && heap==NULL, "<Class>")

- status: works
- tags: resort,singleton,naming,splits
- scope: resort
- source: archery

symptom: Resort-only sport code with no RTTI
cause: singleton create passes the class-name string to the instance check; instance and heap words are adjacent in .sbss
fix: use the string as the file name (Sports2/Arc/Camera.cpp etc.); the instance word marks the start of that file's .sbss. Namespace still unproven, so symbols keep placeholders
