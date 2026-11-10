# fn_80323F30 pool-load schedule: constant locals steer load order but delete dead zero stores

- status: fails
- tags: scheduler,pool,fn_80323F30,RPBow_80323790
- scope: src/Pack/RPSports/RPBowScene/RPBow_80323790.cpp

symptom: 98.4: pool lfs order and zero-store placement differ from target after stb 0x245
cause: Declaring f32 locals for 0.007f/0.02f/0.03f before the zero stores moves the lfs to IR order (loads follow declaration order, pool order too, so only pool-order declarations keep .sdata2) but with 0.007f as a local mwcc drops the 3 dead zero stores (size 1548 vs 1560); volatile zero stores re-load 0.0 into a fresh reg. Moving the 3 zero stores anywhere legal (positions 0x245..before own 0.007 store, all 3 combos, ~800 builds) tops out at 98.9; placing them after the 0.007 store gives 99.1 but is semantically wrong. All-15 locals cause fpr spills (95.7).
fix: None found; fn_80323F30 parked at 98.4. Register colours follow vreg creation (first-use) order descending (f25 = 0.02 ... f19 = 0.9978), loads are scheduled in a different order; needs a shape that keeps first-use vreg order while changing ready-list order.
