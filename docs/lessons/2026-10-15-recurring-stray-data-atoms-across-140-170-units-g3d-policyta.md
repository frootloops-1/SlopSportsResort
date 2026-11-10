# Stray g3d policyTable/cm2hw atoms in ~150 objects are link-time artifacts, not source bugs

- status: works
- tags: data,sdata,sdata2,nw4r,g3d,link,dead-strip,weak,tooling

symptom: tools/data_diff.py showed an extra 8B zeroed .sdata atom (@LOCAL@GetAnmPlayPolicy...@policyTable) in ~159 objects and an extra .sdata2 cm2hw[4] in ~151; the target objects have neither, so those units look data-inexact
cause: the target splits come from the linked DOL, where MWLD already deduplicated weak data (policyTable is scope:weak, one copy at .sdata 0x804BD418 owned by g3d_anmvis) and stripped unreferenced statics (cm2hw survives only in g3d_gpu and g3d_state). Our objects are compared pre-link so they still carry every copy. Our own main.elf has exactly the same survivors (cm2hw at 0x804C0330/0x804C0350, policyTable at 0x804BD418), so the final binary is unaffected
fix: nothing to fix in source or headers. data_diff.py now classes such atoms (no code reference, or @LOCAL@ function-local statics) as STRAY and excludes them from the real-mismatch count. Dead ends tried: global -ipa file in cflags_rp strips them but changes codegen of already-exact functions (116 fns in 27 units regress, 32 vanish, link fails on operator new(ulong,void*)), so the original did not use it; objects built with -prefix SportsPack.mch cannot take a per-object -ipa file anyway (compiler error 10506); const policyTable just moves it to .sdata2. The per-TU include-guard hacks (NW4R_G3D_PLATFORM_GPU_H etc.) are only needed where the stray shifts addends of real constants and lowers a function score
