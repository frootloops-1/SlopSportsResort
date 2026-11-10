# 12-word lwz/stw pair copy: use struct assignment; declare locals at top for r30/r31 order

- status: works
- tags: struct,copy,regalloc,system_halt
- scope: RPGolMain

symptom: for-loop/macro/array copy of 12 words gave 87-99%
cause: load/store pairing and register order
fix: *(struct{u32 w[12];}*)dst = *(...)src gives 100%; declare src then snd at function top; dead assert = if(c>0){if(c<=0)system_halt(...);copy}
