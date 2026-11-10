# resort library: tool data ranges can swallow neighbours' TYPE_NAME strings

- status: works
- tags: resort,library,port

symptom: g3d_anmvis rodata too large
cause: range guessed past object
fix: cut to object size, carve remainder as unk/rodata_<addr>.cpp
