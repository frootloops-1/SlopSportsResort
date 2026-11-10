# resort library: 4-12 bytes short -> align:16 next; compiled neighbour -> -func_align 16 in its cflags

- status: works
- tags: resort,library,port

symptom: link shift after a ported unit
cause: Resort functions 16-byte aligned
fix: align:16 on asm/auto neighbour (carve unk/text_<addr>), -func_align 16 on a compiled one (g3d_reslightset)
