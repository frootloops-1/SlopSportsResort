# KokeshiIcon: MTX44 for C_MTXOrtho, RAD_TO_DEG literal, unused zero/one locals reorder sdata2, merge rodata strings to @stringBase0

- status: works
- tags: mtx44,sdata2-order,rad-to-deg,symbols,fpr
- scope: Pack/RPKernel/RPSysKokeshiIcon

symptom: MakeEdge 98.4 frame 0x10 off; SetupCamera 1-bit sdata2 diff; sdata relocs
cause: MTX34 proj; folded constant 0x42652EE0; split rodata strings
fix: nw4r::math::MTX44 proj; literal 57.29578f; unused 'f32 zero=0.0f, one=1.0f' at fn top moves pool order; merge split strings into @stringBase0 string_table in symbols.txt; declare block temps in reverse for FPR order
