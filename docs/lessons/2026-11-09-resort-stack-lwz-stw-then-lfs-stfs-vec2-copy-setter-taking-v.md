# resort: stack lwz/stw then lfs/stfs VEC2 copy = setter taking VEC2 by value

- status: works
- tags: resort,rp

symptom: odd stack copy before call
cause: by-value struct parameter
fix: ParticleManager::Modifier_SetScale(VEC2)
