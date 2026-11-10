# Param loads interleaved with prologue saves: make the pointer param const

- status: works
- tags: prologue,const,param,scheduling
- scope: RPTns_8024b728
- source: opus worker 2026-10-14

symptom: orig lfs from param between stw r29-r31; ours all stw first
cause: const T* / const T& param allows early load scheduling
fix: declare param const T* (T* const or T& no effect) (fn_8024B8DC)
