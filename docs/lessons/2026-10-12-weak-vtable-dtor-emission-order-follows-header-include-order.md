# Weak vtable/dtor emission order follows header include order; EGG::LightManager sizeof is 0x2C

- status: works
- tags: weak,vtable,include-order,dtor,LightManager,sizeof,array-init,RPGrpModelScene
- scope: RPGrpModelScene
- source: opus worker 2026-10-12

symptom: Fog/Light/Scene vtables and dtors emitted in different order; new RPGrpLightManager allocates 0x24 not 0x2C
cause: Weak emission follows reverse class declaration order; header was missing the 0x24..0x2C fields
fix: Include RPGrpModelScene.h, RPGrpLightManager.h, RPGrpFogManager.h before <Pack/RPGraphics.h>; add char UNK_0x24[0x2C-0x24]; array-clear loop must live in an inline member helper (CreateEntryList) to get the original register assignment; #line N before asserts sets the halt line
