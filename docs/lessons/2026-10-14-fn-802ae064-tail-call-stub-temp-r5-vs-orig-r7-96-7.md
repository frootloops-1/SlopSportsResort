# fn_802AE064 tail-call stub temp r5 vs orig r7 (96.7)

- status: open
- tags: regalloc,stub
- scope: RPGol_802adb7c
- source: fn_802AE064

symptom: mr r5,r3 vs mr r7,r3
cause: unknown; maybe more real params
fix: dead ends: unnamed/(void) int params
