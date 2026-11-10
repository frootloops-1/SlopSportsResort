# Missing frsp on f32 param: (f32)(double)v

- status: works
- tags: mwcc,float,frsp
- scope: RPGol_802bb044
- source: sonnet-worker

symptom: stray/missing frsp f1,f1
cause: double round trip in original
fix: (f32)(double)v in the expression; double param made it worse
