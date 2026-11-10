# Per-row inline SetRow(float*,a,b,c) reproduces lwz reloads between rows

- status: works
- tags: inline,loads
- scope: RPGol_802b4f2c
- source: fn_802B54A0

symptom: merged base loads across row stores
cause: direct array stores CSE the base
fix: inline SetRow helper called with self->f3c per row
