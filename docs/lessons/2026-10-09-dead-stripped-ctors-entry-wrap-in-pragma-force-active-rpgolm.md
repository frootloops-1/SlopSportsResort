# Dead-stripped .ctors entry: wrap in #pragma force_active (RPGolMapObjBase)

- status: works
- tags: golf,ctors,link,force_active,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: opus

symptom: Matching unit: main.dol FAILED, linked .ctors table missing the unit's entry and shifted one word
cause: mwld drops a .ctors word carrying an unreferenced symbol; FORCEACTIVE on the function keeps only the function
fix: #pragma force_active on / reset around the __declspec(section ".ctors") static pointer; global alone does not help; same pattern in RPUtlObject, RPUtlLytFrameCursor, RPUtl_801C9E7C
