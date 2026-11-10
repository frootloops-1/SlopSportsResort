# Target has ONE big lbl_ over several source statics: split it per compiler local

- status: works
- tags: data-ref,symbols,bss,sdata2
- scope: project
- source: claude

symptom: reloc shows ...rodata.0/...bss.0 or lbl_X+off on one side vs separate @N/static on the other
cause: dtk guessed one large symbol over several compiler-emitted locals
fix: split the target symbol in symbols.txt into one symbol per local in our .o (@NNN for compiler locals, source names for statics; same sizes; data:4byte as needed). Do NOT merge the source arrays into a struct (loses base-register pooling, drops to ~75%). sdata2 'size 8' that is one float + TU-end pad: @N size 4 + gap_NN_<addr>_sdata2 size 4. Replace by name AND address (names like ...rodata.0 repeat)
