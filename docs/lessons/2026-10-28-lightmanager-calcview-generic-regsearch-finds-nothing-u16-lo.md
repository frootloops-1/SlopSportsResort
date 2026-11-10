# LightManager CalcView: generic regsearch finds nothing; u16 loop counter and viewNo-as-counter are worse

- status: fails
- tags: lightmanager,calcview,regsearch
- scope: egg/gfxe/eggLightManager

symptom: CalcView r25/r23 swap (pObjSet vs index), baseline regsearch score 23.5 rank 3
cause: function has almost no generic mutation sites (8 evals in 12 min, best = baseline); target r23 role has loop weight w29 vs ours w8
fix: none: 'for (u16 i...)' score 273.5; reusing viewNo as counter 393.5. Source restored. Needs a hand-written sites.json or a new vreg idea; parked
