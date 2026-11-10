# fn_80344650: holder + indexed use makes a row pointer an optimizer IV between loop IVs

- status: works
- tags: holder,regalloc,iv,RPBow_803433E4
- scope: Pack/RPSports/RPBowScene/RPBow_803433E4

symptom: named row pointer obs (obs++ walk) colours last (r26); retail r28 between two lay-walk IVs (r29/r27)
cause: mwcc_dbg: temps @1307/@1310/@1312/@1328 colour in descending vreg before named locals; holder alone puts obs above all (r30, worse); index form obs[j] alone also worse
fix: struct BowObsRef{BowObstacle* p;} obs; obs.p = &...obstacles[(k+1)*16]; use obs.p[j] (no obs++) in the copy loop: harness 39 -> 0 (R17 255)
