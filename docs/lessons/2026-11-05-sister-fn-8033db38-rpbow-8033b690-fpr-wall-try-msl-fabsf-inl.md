# Sister fn_8033DB38 (RPBow_8033B690) FPR wall: try MSL fabsf + inlined weight expressions

- status: open
- tags: RPBow_8033B690,fn_8033DB38,fpr,fabsf
- scope: Pack/RPSports/RPBowScene

symptom: fn_8033DB38 velocity-block FPR wall parked as scheduler wall
cause: same contact code shape as fn_803395E4, which closed via fabsf inline and inlining wi/wj
fix: untested: apply fabsf(dot) for vi/vj, imp before weights, weights inlined into the impulse expressions
