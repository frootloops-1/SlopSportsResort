# RPUtl_801BFEA8 flip: three fixes, sdata2 gap was not a problem

- status: works
- tags: ctors,force_active,math_arithmetic,sdata2,gap,flip
- source: RPUtl_801BFEA8

symptom: 100% objdiff unit gave 161 DOL diff bytes
cause: OS.h stray static inline text via math_arithmetic.h; missing .ctors word; sdata2 4-byte split gap is just section padding
fix: define NW4R_MATH_ARITHMETIC_H + declare FrSqrt/FSqrt/U16ToF32; force_active __declspec(section .ctors) ptr to empty fn; sdata2 gap needed nothing (links fine); flipped, DOL 0 diff
