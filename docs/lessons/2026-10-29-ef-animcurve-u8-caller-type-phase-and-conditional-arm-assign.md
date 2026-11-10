# ef_animcurve U8 caller type phase and conditional arm assignments reach 99.54622

- status: works
- tags: ef_animcurve,U8,FPR,register-allocation,conditional
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: After99.44958, right-only interpolation type9/a10 wrong; four e branch inversions remain.
cause: Caller-owned type local makes a temp colour first; declaration before b reverses remaining b/type pair. Discarded conditional expression preserves ternary branch lowering while assigning high named e directly; dead result phi disappears.
fix: Right-only caller u8 type immediately beforestore99.47899/72lines; baretype before b declaration99.52941/46. U8Interp baree plus discarded ternary (e=0):(e=1.5)99.54622/38lines, target FPRs/branch directions. No new helper, no other function regressions. Initial/final table and key-setup GPR groups remain.
