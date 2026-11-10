# if (d > 0) dist = FSqrt(d) reproduces the extra ble before FSqrt's cror

- status: works
- tags: fsqrt,nw4r,branch
- scope: mwcc
- source: RPTns_802390b0

symptom: orig fcmpo;ble;cror eq,lt,eq;bne;b with result preset to 0; ours lacks the ble and recomputes the arg after FrSqrt
cause: source guarded FSqrt with an explicit > 0 test on a variable
fix: f32 d = rr - p*p; f32 dist = 0.0f; if (d > 0.0f) dist = nw4r::math::FSqrt(d); reuse the same d variable for a second sqrt to get the same FPR
