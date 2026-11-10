# resort: kokeshi ChangeTexture (93.8) and GetModelBaseScaleInvalidatedMtx (84.8 prologue) resist source variants

- status: open
- tags: resort,RPSysKokeshiManager,scheduling
- scope: resort
- source: RP batch 5 (2026-11-09)

symptom: late pX+0x68/+0xA4 loads; base-scale word copies before lfs 1.0f/LR save in the prologue
cause: unknown (ogws compiler output schedules like ours for the second)
fix: 8 ideas failed for ChangeTexture, 10 for the prologue; candidates for a diagnosed permuter run or a different inline shape
