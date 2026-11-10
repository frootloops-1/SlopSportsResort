# sdata2 order led by a later function's constants

- status: works
- tags: sdata2,pool-order,rpbsb
- source: RPBsb_8028c450 2026-10-16

symptom: .sdata2 starts with 255,20 used by a later function
cause: constants pooled in first-use order
fix: dead static helper using 255.0f*t/20.0f placed first (stripped at link)
