# lbz x4 colour copy interleaved with earlier lwz: local aggregate-init GXColor by value

- status: works
- tags: sdata2,color
- scope: RPGol_802aaf88
- source: fn_802AB144

symptom: 77% scheduling
cause: static/extern const copy
fix: _GXColor c = {255,255,255,255}; pass c by value (anonymous .sdata2 object)
