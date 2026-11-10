# FP register order of two float locals follows declaration order

- status: works
- tags: float,regalloc,declaration-order,lerp
- scope: RPTns_80218f9c
- source: claude 2026-10-14

symptom: frac/1-frac in f3/f4 swapped (99.1); reordering assignments/inlining did not help
cause: MWCC assigns FP regs by declaration order, not first assignment
fix: declare the later-computed local first, uninitialised at function top (f32 inv; f32 frac;) then assign (fn_802190E0 -> 100)
