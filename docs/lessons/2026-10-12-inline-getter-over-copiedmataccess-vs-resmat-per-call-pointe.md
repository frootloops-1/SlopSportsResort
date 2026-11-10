# Inline getter over CopiedMatAccess vs ResMat; per-call pointer reload

- status: works
- tags: RPGrpModelMaterial,inline,branch-layout,mwcc
- scope: RPGrpModelMaterial.cpp
- source: claude 2026-10-12

symptom: Getter that picks CopiedMatAccess else ResMat matched only 90-94%; pointer element reloaded at each call site; r30/r31 swap
cause: Source shape: early-return form and indexing into a local changed branch layout/caching
fix: if (!HasCopiedMat()) return res.GetX(); r=acc.GetX(false); if (r.IsValid()) return r; return res.GetX(); and pass *p directly iterating const u8* p, declaring p before found
