# sdata2 pool order: int-to-float double after the fn's float literals

- status: works
- tags: sdata2,pool-order,rpbsb
- source: RPBsb_802803b0 2026-10-16

symptom: pool 1.0,pad,dbl,0.0,480,... not reproduced
cause: magic double is created after the same function's float literals
fix: several dead static helpers in generation order, one literal group each (21 -> 30 exact fns)
