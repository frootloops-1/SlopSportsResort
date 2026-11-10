# resort: a parameter load hoisted above the prologue stores means the pointer param is const T*

- status: works
- tags: resort,regalloc,const,prologue,RPGrpShadowTexture
- scope: resort
- source: RP batch 5 (2026-11-09)

symptom: retail loads lwz 0x44(r4) between mflr and stw r0; ours after the prologue (87%, looked like scheduling)
cause: MWCC Wii/1.3 only hoists a load through a const-qualified pointer parameter above the prologue stores
fix: make the param const T* (Unk_ placeholder mangling is not evidence); m_arr[call()].field via a reference local avoids the int idx mulli order and the bool clrlwi
