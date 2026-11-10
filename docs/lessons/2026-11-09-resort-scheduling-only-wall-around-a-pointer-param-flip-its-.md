# resort: scheduling-only wall around a pointer param -> flip its const qualifier

- status: works
- tags: resort,mwcc,scheduling,const,kokeshi

symptom: Same instructions and registers, only load order differs relative to prologue saves or argument setup
cause: Const-ness of the pointee decides whether MWCC 1.3 treats loads through it as aliasing stack stores; ogws-derived mangled names can carry the wrong const
fix: Kokeshi GetModelBaseScaleInvalidatedMtx needed const RPGrpModel* (84.8->100), ChangeTexture needed non-const RPSysKokeshiUnkTex* (93.8->100). A permuter state that routes &param through a dummy pointer and fixes only the schedule points at this
