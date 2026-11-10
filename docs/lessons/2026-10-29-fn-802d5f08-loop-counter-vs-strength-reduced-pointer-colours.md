# fn_802D5F08: loop counter vs strength-reduced pointer colours fixed by moving the loop into a static inline helper

- status: works
- tags: RPBox_802cf93c,regalloc,mwcc_dbg,loop
- scope: RPBox

symptom: for(i<2) with self->p4F8[i]: target i r29 / SR pointer r28, ours swapped
cause: mwcc_dbg: named i = r33, front-end SR temp r35 > i so it is coloured first; a named pointer local fixes colours but changes the lwz displacement to 0(rX)
fix: move loop into static inline helper (name inferred) taking self and BoxVec3& v: i becomes an @inline var with a vreg above the SR temp; 99.7->100
