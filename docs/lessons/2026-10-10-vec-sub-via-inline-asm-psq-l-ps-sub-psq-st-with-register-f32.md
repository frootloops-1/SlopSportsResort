# Vec sub via inline asm psq_l/ps_sub/psq_st with register f32 w0,w1,w2 matches exactly (fn_80296E30)

- status: works
- tags: rpgolmapobjtree,paired-single,inline-asm
- scope: RPGolMapObjTree
- source: sonnet

symptom: paired-single vec sub
cause: orig uses nw4r-style asm helper
fix: extern C fn with register f32 w0,w1,w2; psq_l w2,0(a); psq_l w1,0(b); ps_sub w0,w2,w1; ... psq_st
