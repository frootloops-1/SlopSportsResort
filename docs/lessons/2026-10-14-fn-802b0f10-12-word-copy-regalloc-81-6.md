# fn_802B0F10 12-word copy regalloc (81.6)

- status: open
- tags: regalloc,copy
- scope: RPGol_802b08a0
- source: fn_802B0F10

symptom: orig d0->r29, d11->r0; locals give r0 to first-stored value
cause: unknown
fix: struct copy from inline-ctor temp reproduces allocation but keeps dead stack stores (41%); best kept 124B vs 132B; same-size variant 79.7
