# resort: subic/subfe bool normalisation before an index = BOOL || helper stored in a bool local

- status: works
- tags: resort,rp

symptom: extra subic/subfe
cause: BOOL to bool conversion
fix: store the BOOL-returning helper result in a bool local (RPSysParticleManager::Calc)
