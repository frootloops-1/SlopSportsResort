# Wrong-overload / wrong-linkage RELOC near-misses: check extern C, const-ness of ctor param, int vs u32 index

- status: works
- tags: reloc,overload,extern-c
- scope: egg/gfxe

symptom: RELOC bucket: bl names differ only in mangling (PCQ vs PQ, CFi vs CFUl, plain vs __FP...)
cause: declarations differ from original: pointer-to-const param, int vs u32 argument overload, missing extern C
fix: eggG3DUtility: (int)id for ResMdl::GetResNode/GetResMat, GetInvCameraMtxPtr not ProjectionTex; LightTexture ctor takes const LightTextureManager*; define static members so object links -> Matching
