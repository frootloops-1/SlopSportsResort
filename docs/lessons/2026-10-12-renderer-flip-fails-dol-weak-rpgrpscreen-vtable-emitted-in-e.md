# Renderer flip fails DOL: weak RPGrpScreen vtable emitted in earlier TU (Renderer before Screen in link order)

- status: open
- tags: layout,weak,vtable,link-order,RPGrpScreen,DOL,policyTable,sdata
- scope: RPGrpRenderer

symptom: All code exact (22/25) but DOL has ~4600 diffs; .data +0x11 and .sdata +8 vs the split, shifting every later section
cause: Original RPGrpScreen vtable is GLOBAL in RPGrpScreen.cpp (0x803B9894) while __dt__11RPGrpScreen is weak earlier; ours header has no out-of-line virtual so every TU emits a weak vtable and Renderer (linked before Screen) wins it. Also weak policyTable (.sdata 8B) from g3d_anmobj.h
fix: open: need a key function (out-of-line virtual override of EGG::Screen::SetProjectionGX or CopyToG3D?) defined in RPGrpScreen.cpp so the vtable is emitted only there; careful: RPGrpScreen.cpp is Matching. Flip only after the DOL check
