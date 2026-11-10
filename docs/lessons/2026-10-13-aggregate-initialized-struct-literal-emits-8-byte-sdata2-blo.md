# Aggregate-initialized struct literal emits 8-byte .sdata2 blob per fn

- status: works
- tags: mwcc,sdata2,literal
- source: RPGol_802b90b4

symptom: GolV2 v={1000.0f,0.0f} duplicated 8-byte aggregate in .sdata2; orig lfs two pooled scalars
cause: aggregate init of local struct
fix: member-wise assignment v.x=1000.0f; v.y=0.0f; pools scalar floats
