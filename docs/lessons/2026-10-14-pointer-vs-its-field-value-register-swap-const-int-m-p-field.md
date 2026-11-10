# Pointer vs its field value register swap: const int& m = p->field

- status: works
- tags: regalloc
- scope: RPGol_802aaf88
- source: fn_802AC2B0

symptom: r5/r6 swap
cause: value copy
fix: const int& m = b->f94;
