# 32767.0f + itof magic leading .sdata2: non-inline static helper at file end

- status: works
- tags: sdata2,pool-order,rand,helper
- scope: RPTns_8022d590
- source: sonnet worker 2026-10-14

symptom: pool starts with 32767.0 and 0x4330 double before first fn's literals
cause: static helper defined at end of source (inlined by -inline auto) emits its literals first
fix: static f32 tnsRandF(){return (f32)tnsRand15()/32767.0f;} forward-declared, defined last (RPTns_8022d590)
