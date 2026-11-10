# resort bowling: declaration order fixes prologue and r27/r29 swap in BackgroundNpcManager::Render

- status: works
- tags: resort,bowling

symptom: saved-register order differs
cause: local declaration order drives allocation
fix: declare pConfig before stateFlag; RPGrpModel* pBody before pGroup
