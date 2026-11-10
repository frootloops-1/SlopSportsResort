# RVL SDK + RPKernel data 100%: explicit gap_ symbols, padded sizes, lbl_ names, surplus-function extab

- status: works
- tags: data,symbols,gap,extab,sdk,rpkernel
- scope: revolution/*, MetroTRK, MSL, runtime, Pack/RPKernel

symptom: Units Matching at DOL 0 but data sections 85-99% in objdiff (RVL SDK category 99.79%, RPKernel 6.6k bytes short)
cause: Explicit gap_NN_ symbols and padded trailing sizes in symbols.txt that the compiled object lacks; lbl_/odd names for compiled locals; inline header functions or ported-but-dead-stripped functions adding extra extab entries; dtk missing an extab dtor-pointer reloc; g3d_gpu.h cm2hw sdata2 pad
fix: delete explicit gap_ lines (dtk regenerates hidden gaps); trim symbol size to compiled size; rename lbl_ to compiled name; hcisu_h2/uusb_ppc bss start moved to the 32-aligned symbol; narrow include (revolution/OS/OS.h not rvl/OS.h) to drop OSFastCast inline extab; #if 0 for dead-stripped surplus functions (mbstring, math_api); config.yml add_relocations for NMWException extab; pre-define NW4R_G3D_PLATFORM_GPU_H in RPKernel units; single-line DOL 0 + sym_addr_check unchanged
