# Many-float struct copy needs reverse-declared locals (RPGolMapObjBase)

- status: works
- tags: golf,float,copy,psq,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: sonnet

symptom: 15 float copy; struct assign/loop gives interleaved lfs/stfs (42%/11%); prologue psq_st f31
cause: register assignment follows local declaration order
fix: f32 t14..t0 declared in reverse order in one declaration, load t0..t14 ascending then store
