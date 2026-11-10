# RPGrpModel.h include emits stray .sdata in golf TUs

- status: works
- tags: golf,include,sdata,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: haiku

symptom: extra GetAnmPlayPolicy policyTable .sdata
cause: header static data
fix: declare member as extern C UpdateFrame__10RPGrpModelFv(void*) instead of including header
