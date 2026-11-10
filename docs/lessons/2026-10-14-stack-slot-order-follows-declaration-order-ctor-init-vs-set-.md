# Stack slot order follows declaration order; ctor-init vs set() copy kind

- status: works
- tags: stack,struct-copy
- scope: RPGol_802b7df8
- source: fn_802B7FEC

symptom: locals at swapped stack slots; lfs/stfs vs lwz/stw copies
cause: decl order; ctor initializers copy as words
fix: declare the lower-slot local first with default ctor and fill via inline set(); copy floats through a {u32 a,b,c} view for lwz/stw
