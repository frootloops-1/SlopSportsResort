# a + K canonicalised to fadds K,a: static inline add helper

- status: works
- tags: float,fadds,fmuls,operand-order,inline
- scope: RPTns
- source: RPTns_80220994

symptom: fadds operands swapped vs original
cause: MWCC canonicalises const operand
fix: static inline f32 TnsAdd(f32 a,f32 b){return a+b;} keeps (a,K) order; same for TnsMul
