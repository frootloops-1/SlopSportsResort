# Tiny inline weak virtuals score 0 until symbols.txt placeholder is renamed

- status: works
- tags: symbols.txt,inline,weak,virtual,On,Off,IsEnable,naming
- scope: RPGrpDrawPathManager
- source: haiku worker + coordinator 2026-10-12

symptom: fn_801A97B8 etc score 0 though our weak symbols have identical bodies
cause: objdiff pairs by name; target uses fn_XXXX placeholder
fix: Rename in config/RSPE01_01/symbols.txt to mangled name with scope:weak (precedent: RPGrpDrawPathShadowTexture)
