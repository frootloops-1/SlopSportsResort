# ef_animcurve U8 search variable order reaches 99.44958; positive e spelling flat

- status: works
- tags: ef_animcurve,U8,register-allocation,search,FPR
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: After interpolation gain, U8 lo5/mid6 vs targetlo6/mid5, four e branch inversions remain.
cause: lo/mid named order determines their interfering volatile colours; positive vs negative direct e if canonicalizes.
fix: Bare mid before lo initializer, assignment mid=hi/2 at prior site:99.390755->99.44958/86lines. idx before loFrame earlier99.09664->99.18908. Positive e if identical99.390755/110lines and rejected flat. Saved roles preserved. Actual dumps u8-interp-e/u8-mid; no full match.
