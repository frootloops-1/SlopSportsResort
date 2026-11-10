# fmadds fusion avoided with separate product temp

- status: works
- tags: mwcc,float,fmadds
- scope: RPGol_802bb608
- source: opus-worker

symptom: r += 0.1f*f() fused into fmadds; orig fmuls+fadds
cause: MWCC fuses mul-add in one expression
fix: f32 t = 0.1f*f(); r += t;
