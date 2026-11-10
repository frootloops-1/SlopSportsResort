# RPUtlMapData fn_801BF6C4: inline-lookup register residue, 20 source variants no gain

- status: fails
- tags: register,inline,mapdata,r12
- scope: src/Pack/RPUtility/RPUtlMapData.cpp

symptom: outer loop count lands in r30 (target r12), lookup hdr/entryCount r31/r12 (target r30/r31); 14 diff lines
cause: coloring order of count vs inlined lookup temps; not weight (extra uses of count did not move it) and not declaration order alone
fix: No fix. Tried direct cond, in-block decl, for-init, while/do-while, guard, dup cond, count reuse for pathCount, path-update reshapes, cached-header inline helper. Permuter base.c must define 564 or the lookup is not inlined.
