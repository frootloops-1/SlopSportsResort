# const T* param hoists constant loads (fn_803024C0 94.7 -> 100); compare against literal not the variable holding it; hand vtables need defer_codegen off

- status: works
- tags: const-pointee,vtable,pool-order,RPBox_803024c0
- scope: RPBox_803024c0

symptom: fn_803024C0 94.7: lfs consts before param pointer load; fn_8030264C 90.5; .data 0
cause: non-const param pointer; compare against variable a=0.0f merged the CSE'd constant
fix: const BoxSwayOwner* owner; if (m > 0.0f); 0.05f*BoxDt(); hand void* vtables after #pragma defer_codegen off (else ctor uses ...data.0 anchor, 76%). fn_8030264C 93.6: retail keeps &tbl[2]/&tbl[1] in addi temps (4 extra insns); ref/pointer locals, inline &tbl[i], (lo,hi) helpers, *lo++ all fold. Parked.
