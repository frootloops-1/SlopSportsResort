# String pool order: codegen order, reverse of source; dead placeholder static fn last in source pools first

- status: works
- tags: rodata,string,pool,dead-strip,placeholder
- scope: RPGolMain

symptom: pool order breff,breft,glf... differs from first-use order in the only user fn
cause: pooled literals added at codegen time; original had a linker-stripped function generated before the user
fix: static inline GolLoadEffect() called from fn and from an unreferenced static fn placed LAST in source (generated first); linker strips it, main.dol still OK
