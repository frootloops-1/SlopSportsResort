# ef_animcurve Rotate uniform existing range and sign helpers regress

- status: fails
- tags: ef_animcurve,Rotate,register-allocation,inline
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Rotate 98.467865, 172 normalized changed lines; volatile random/sign locals differ alongside saved colours.
cause: Uniform boundaries change inline-vreg identity but not toward the retail allocation.
fix: Existing GetRandomRangeStride at all five lookups: 97.967865/360 changed lines. Existing RotSign at all five sign sites: 98.31191/234. Both reverted after two no-gain tries; no new helpers.
