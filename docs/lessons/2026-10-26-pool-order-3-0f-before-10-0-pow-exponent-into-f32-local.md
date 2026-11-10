# Pool order -3.0f before 10.0: pow exponent into f32 local

- status: works
- tags: sdata2,pool,pow,axfx
- scope: src/revolution/AXFX
- source: axfx-1026

symptom: AXFX Dpl2 __InitParams .sdata2 81%
cause: constant materialisation order follows evaluation order
fix: compute the exponent into an f32 local before the pow call: 81 -> 100
