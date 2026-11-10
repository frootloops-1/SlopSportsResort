# Inline-helper transpose temps decl order differs from top-level (RPGolMapObjBase)

- status: works
- tags: golf,float,inline,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: sonnet

symptom: fN registers reversed inside static inline helper
cause: alloc order context dependent
fix: inside helper declare t11..t0 reverse; top-level fn needs ascending
