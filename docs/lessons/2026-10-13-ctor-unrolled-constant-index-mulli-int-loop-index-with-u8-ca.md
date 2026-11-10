# Ctor unrolled constant-index mulli: int loop index with (u8) cast in subscript

- status: works
- tags: mulli,ctor,unrolled,loop,u8-cast
- scope: Pack/RPKernel

symptom: ctor 82.4/74.6: li rX,0; mulli i*0x1c folded
cause: loop forms fold offsets
fix: for(int i<N) mButton[(u8)i].reset() keeps li+mulli; other index types/forms fold. Also unrolled for(int i<2) with SetVisible(field==i) gives subfic; merge rodata labels into @stringBase0 string_table with true size
