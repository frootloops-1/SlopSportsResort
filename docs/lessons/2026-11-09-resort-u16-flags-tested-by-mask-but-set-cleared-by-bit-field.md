# resort: u16 flags tested by mask but set/cleared by bit-field -> union raw/bit-field

- status: works
- tags: resort,bitfield,RPGrpRenderer
- scope: resort
- source: rp9-renderer

symptom: rlwinm 30,28 / ori for set/clear but andi. tests
cause: &= ~4 and TBitFlag give andi.; bit-field assignment gives rlwinm/ori
fix: union { u16 raw; struct {bit-fields} }; test raw by mask, set/clear via bit-field. Also: virtual call on a local EGG object stays virtual only with the real EGG class (local class devirtualizes)
