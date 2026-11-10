# RPUtl_801C67B8 pool repeats 1.0/0.0 and pads to 8 mid-range: unit is several TUs

- status: open
- tags: sdata2,splits,pool
- scope: Pack/RPUtility/RPUtl_801C67B8
- source: claude/rputl-c67b8-1027

symptom: hand extern-const pool + gap words; compiler still appends two 0x43300000 magic doubles (+16 bytes); literal rewrite merges duplicates TU-wide
cause: retail .sdata2 has 1.0 x4, 0.0 x3 and 8-byte end padding at 0x804C1BCC and 0x804C1C0C, which one MWCC TU does not produce
fix: orchestrator: split 801C67B8..8330 into SampleBuffer / FilterOwner / Filter / Replay TUs (pool BA0..BCF, BD0..BD7, BD8..BDF, BE0..C0F), then literals + pool_renames
