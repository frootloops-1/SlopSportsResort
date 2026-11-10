# Pool aggregate created by C between seeded literals: split the seed

- status: works
- tags: seed,sdata2,aggregate
- scope: RPBsbScene
- source: RPBsb_8027039c/80283fe0

symptom: anonymous 4-byte aggregate (0xFFFFFFFF, 0x00FF00FF) lands after the seeded floats
cause: aggregate is created when its C function is compiled, after the seed helper
fix: move the literals that follow it into a second never-called seed placed after that C function
